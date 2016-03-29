;; GCC machine description for Intel MIC instructions
;; Copyright (C) 2011
;; Free Software Foundation, Inc.
;;
;; This file is part of GCC.
;;
;; GCC is free software; you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation; either version 3, or (at your option)
;; any later version.
;;
;; GCC is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.
;;
;; You should have received a copy of the GNU General Public License
;; along with GCC; see the file COPYING3.  If not see
;; <http://www.gnu.org/licenses/>.

(define_mode_iterator KNC_MOVMISALIGN_MODE [SF DF TF DI])
(define_mode_iterator KNC_MOVMISALIGN_NOTF_MODE [SF DF DI])
(define_mode_attr KNC_MOVMISALIGN_MIN_MODE
  [(SF "SF") (DF "DF") (TF "TF") (DI "DI")])
(define_mode_attr knc_movmisalign_int_mode
  [(SF "SI") (DF "DI") (TF "DI") (DI "DI")])

(define_mode_iterator KNC_STORE_MODE [SI DI TI SF DF TF])
(define_mode_attr knc_store_suffix
  [(SI "d") (DI "q") (TI "q") (SF "ps") (DF "pd") (TF "q")])

(define_expand "knc_reload_inti"
  [(parallel [(match_operand:TI 0 "register_operand" "")
	      (match_operand:TI 1 "register_operand" "")
	      (match_operand:HI 2 "register_operand" "=&r")])]
  "TARGET_KNC"
{
  rtx mem = assign_386_stack_local (TImode, SLOT_TEMP);
  emit_move_insn (mem, operands[1]);
  emit_move_insn (operands[0], mem);
  DONE;
})

;; KNC output reload.
(define_expand "knc_reload_out<mode>"
  [(parallel [(match_operand:KNC_STORE_MODE 0 "memory_operand" "")
	      (match_operand:KNC_STORE_MODE 1 "register_operand" "")
	      (match_operand:HI 2 "register_operand" "=&r")])]
 "TARGET_KNC"
{
  if (!misaligned_operand(operands[0], <MODE>mode))
    {
      ix86_expand_knc_store (operands[0], operands[1],
			     gen_rtx_REG (HImode, MASK2_REG),
			     operands[2]);
      DONE;
    }
  else
    {
      switch (GET_MODE (operands[0]))
	{
	case SFmode:
	  emit_insn( gen_movmisalignsf (operands[0], operands[1]));
	  DONE;
	  break;

	case DFmode:
	  emit_insn (gen_movmisaligndf (operands[0], operands[1]));
	  DONE;
	  break;

	case TFmode:
	  emit_insn (gen_movmisaligntf (operands[0], operands[1]));
	  DONE;
	  break;

	case DImode:
	  emit_insn (gen_movmisaligndi (operands[0], operands[1]));
	  DONE;
	  break;

	default:
	  FAIL;
	}
    }
})

;; Scalar store for KNC vector registers.
(define_insn "knc_store<mode>"
  [(set (match_operand:KNC_STORE_MODE 0 "memory_operand" "=m")
	(unspec:KNC_STORE_MODE [
	   (match_operand:KNC_STORE_MODE 1 "register_operand" "v")
           (match_operand:HI 2 "register_operand" "Yk")] UNSCPEC_KNC_NO_SEC_RELOAD))]
  "TARGET_KNC"
{
  gcc_assert (! misaligned_operand(operands[0], <MODE>mode));
  return "vpackstorel<knc_store_suffix>\t{%g1, %M0%{%2%}|%M0%{%2%}, %g1}";
}
  [(set_attr "type" "ssemov")
   (set_attr "mode" "<MODE>")])

;; Load a constant integer into mask register.
(define_insn_and_split "knc_load_mask_reg_hi"
  [(set (match_operand:HI 0 "register_operand" "=k")
	(unspec:HI [(match_operand:HI 1 "const_int_operand" "n")]
		   UNSPEC_LOAD_MASK_REG))]
  "TARGET_KNC"
  "#"
  "&& reload_completed"
  [(const_int 0)]
  "ix86_split_load_mask_reg (curr_insn, operands[0], operands[1]); DONE;"
  [(set_attr "type" "multi")])

;; DImode load expander for integer register and KNC vector register.
(define_expand "knc_load_misalign_di"
  [(set (match_operand:DI 0 "register_operand" "")
	(match_operand:DI 1 "memory_operand" ""))]
  "TARGET_KNC"
{
  rtx reg = gen_reg_rtx (HImode);
  rtx mask = gen_rtx_REG (HImode, MASK1_REG);
  emit_move_insn (reg, CONST1_RTX (HImode));
  emit_move_insn (mask, reg);
  emit_insn (gen_knc_load_misalign_di_1 (operands[0], operands[1], mask));
  DONE;
})

;; DImode load for integer register and KNC vector register.
(define_insn "knc_load_misalign_di_1"
  [(set (match_operand:DI 0 "register_operand" "=r,v")
	(match_operand:DI 1 "memory_operand" "m,m"))
   (use (match_operand:HI 2 "register_operand" "Yk,Yk"))]
  "TARGET_KNC"
  "#")

;; DImode load for integer register and aligned DImode load for KNC
;; vector register.
(define_split
  [(set (match_operand:DI 0 "register_operand" "")
	(match_operand:DI 1 "memory_operand" ""))
   (use (match_operand:HI 2 "register_operand" ""))]
  "TARGET_KNC
   && reload_completed
   && (GENERAL_REG_P (operands[0])
       || (GET_CODE (operands[0]) == SUBREG
	   && GENERAL_REG_P (SUBREG_REG (operands[0])))
       ||  !misaligned_operand(operands[1], DImode))"
  [(set (match_dup 0) (match_dup 1))])

;; Misaligned DImode load for KNC vector register.
(define_split
  [(set (match_operand:DI 0 "sse_reg_operand" "")
	(match_operand:DI 1 "memory_operand" ""))]
  "TARGET_KNC
   && reload_completed
   && misaligned_operand(operands[1], DImode)"
  [(const_int 0)]
{
  rtx m_low = adjust_address (operands[1], SImode, 0);
  rtx m_high = adjust_address (operands[1], SImode, 4);
  rtx mask = gen_rtx_REG (HImode, MASK2_REG);
  emit_insn (gen_knc_broadcast_vec_si2di (operands[0], m_high));

  ix86_split_load_mask_reg (curr_insn, mask, CONST1_RTX (HImode));

  emit_insn (gen_knc_masked_merge_load_vec_si2di (operands[0], m_low, mask));

  DONE;
})

(define_split
  [(set (match_operand:DI 0 "register_operand" "")
	(match_operand:DI 1 "memory_operand" ""))
   (use (match_operand:HI 2 "register_operand" ""))]
  "TARGET_KNC
   && reload_completed
   && misaligned_operand(operands[1], DImode)"
  [(const_int 0)]
{
  rtx m_low = adjust_address (operands[1], SImode, 0);
  rtx m_high = adjust_address (operands[1], SImode, 4);
  emit_insn (gen_knc_broadcast_vec_si2di (operands[0], m_high));
  emit_insn (gen_knc_masked_merge_load_vec_si2di (operands[0], m_low,
						  operands[2]));
  DONE;
})

;; Masked merging load SI to DI for KNC vector register.
(define_insn "knc_masked_merge_load_vec_si2di"
  [(set (match_operand:DI 0 "register_operand" "=v")
	(unspec:DI [(match_dup 0)
		    (match_operand:SI 1 "memory_operand" "m")
		    (match_operand:HI 2 "register_operand" "Yk")]
		   UNSPEC_MASKED_MERGE_MOVE))]
  "TARGET_KNC"
{
  gcc_assert (!misaligned_operand(operands[1], SImode));
  return "vpbroadcastd\t{%M1, %g0%{%2%}|%g0%{%2%}, %M1}";
}
  [(set_attr "type" "ssemov")
   (set_attr "mode" "SI")])

;; Broadcast SI to DI for MIC vector register.
(define_insn "knc_broadcast_vec_si2di"
  [(set (match_operand:DI 0 "register_operand" "=v")
	(ior:DI
	  (zero_extend:DI
	    (match_operand:SI 1 "memory_operand" "m"))
	  (ashift:DI
	    (zero_extend:DI (match_dup 1))
	    (const_int 32))))]
  "TARGET_KNC"
{
  gcc_assert (!misaligned_operand(operands[1], SImode));
  return "vpbroadcastd\t{%M1, %g0|%g0, %M1}";
}
  [(set_attr "type" "ssemov")
   (set_attr "mode" "SI")])

(define_expand "movmisalign<mode>"
  [(set (match_operand:KNC_MOVMISALIGN_MODE 0 "nonimmediate_operand" "")
	(match_operand:KNC_MOVMISALIGN_MODE 1 "nonimmediate_operand" ""))]
  "TARGET_KNC"
{
  if ((MEM_P (operands[0])
       && (misaligned_operand(operands[0], <KNC_MOVMISALIGN_MIN_MODE>mode)))
      || (MEM_P (operands[1])
	  && (misaligned_operand(operands[1], <KNC_MOVMISALIGN_MIN_MODE>mode))
	  /* See comment in ix86_expand_move.  */
	  && (<MODE>mode != DImode
	      || MEM_ALIGN (operands[1]) != GET_MODE_ALIGNMENT (SImode))))
    {
      rtx mem = assign_386_stack_local (<MODE>mode, SLOT_TEMP);
      emit_insn (gen_knc_movmisalign<mode> (operands[0], operands[1],
					    mem));
      DONE;
    }
})

(define_insn_and_split "knc_movmisaligntf"
  [(set (match_operand:TF 0 "nonimmediate_operand" "=v,m")
	(unspec:TF [
	  (match_operand:TF 1 "nonimmediate_operand" "m,v")
	  (clobber (match_operand:TF 2 "memory_operand" "=m,m"))
	  (clobber (match_scratch:DI 3 "=&r,&r")) ] UNSCPEC_KNC_NO_SEC_RELOAD))]
  "TARGET_KNC"
  "#"
  "&& reload_completed"
  [(const_int 0)]
  "ix86_expand_move_misalign (TFmode, operands); DONE;"
  [(set_attr "type" "multi")])

(define_insn_and_split "knc_movmisalign<mode>"
  [(set (match_operand:KNC_MOVMISALIGN_NOTF_MODE 0 "nonimmediate_operand" "=r,m,v,m")
	(unspec:KNC_MOVMISALIGN_NOTF_MODE [
	  (match_operand:KNC_MOVMISALIGN_NOTF_MODE 1 "nonimmediate_operand" "m,r,m,v")
          (clobber (match_operand:KNC_MOVMISALIGN_NOTF_MODE 2 "memory_operand" "=m,m,m,m"))
          (clobber (match_scratch:<knc_movmisalign_int_mode> 3 "=&r,&r,&r,&r")) ] UNSCPEC_KNC_NO_SEC_RELOAD))]
  "TARGET_KNC"
  "#"
  "&& reload_completed"
  [(const_int 0)]
  "ix86_expand_move_misalign (<MODE>mode, operands); DONE;"
  [(set_attr "type" "multi")])
