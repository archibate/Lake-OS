#pragma once
typedef union L4m_fault_info {
	reg_t data[2];
	struct {
		reg_t pf_errcd, pf_offset;
	};
} L4m_fault_info_t;
typedef union L4m_fault_result {
	reg_t data[2];
	struct {
		reg_t sv_mask, sv_buff;
	};
} L4m_fault_result_t;
