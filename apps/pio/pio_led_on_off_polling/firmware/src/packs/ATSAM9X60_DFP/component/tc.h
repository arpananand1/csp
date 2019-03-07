/**
 * \brief Component description for TC
 *
 * Copyright (c) 2019 Microchip Technology Inc. and its subsidiaries.
 *
 * Subject to your compliance with these terms, you may use Microchip software and any derivatives
 * exclusively with Microchip products. It is your responsibility to comply with third party license
 * terms applicable to your use of third party software (including open source software) that may
 * accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY,
 * APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND
 * FITNESS FOR A PARTICULAR PURPOSE.
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF
 * MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT
 * EXCEED THE AMOUNT OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 */

/* file generated from device description version 2019-02-20T18:44:00Z */
#ifndef _SAM9X_TC_COMPONENT_H_
#define _SAM9X_TC_COMPONENT_H_

/* ************************************************************************** */
/*   SOFTWARE API DEFINITION FOR TC                                           */
/* ************************************************************************** */

/* -------- TC_CCR : (TC Offset: 0x00) ( /W 32) Channel Control Register -------- */
#define TC_CCR_CLKEN_Pos                      _U_(0)                                               /**< (TC_CCR) Counter Clock Enable Command Position */
#define TC_CCR_CLKEN_Msk                      (_U_(0x1) << TC_CCR_CLKEN_Pos)                       /**< (TC_CCR) Counter Clock Enable Command Mask */
#define TC_CCR_CLKEN(value)                   (TC_CCR_CLKEN_Msk & ((value) << TC_CCR_CLKEN_Pos))  
#define TC_CCR_CLKDIS_Pos                     _U_(1)                                               /**< (TC_CCR) Counter Clock Disable Command Position */
#define TC_CCR_CLKDIS_Msk                     (_U_(0x1) << TC_CCR_CLKDIS_Pos)                      /**< (TC_CCR) Counter Clock Disable Command Mask */
#define TC_CCR_CLKDIS(value)                  (TC_CCR_CLKDIS_Msk & ((value) << TC_CCR_CLKDIS_Pos))
#define TC_CCR_SWTRG_Pos                      _U_(2)                                               /**< (TC_CCR) Software Trigger Command Position */
#define TC_CCR_SWTRG_Msk                      (_U_(0x1) << TC_CCR_SWTRG_Pos)                       /**< (TC_CCR) Software Trigger Command Mask */
#define TC_CCR_SWTRG(value)                   (TC_CCR_SWTRG_Msk & ((value) << TC_CCR_SWTRG_Pos))  
#define TC_CCR_Msk                            _U_(0x00000007)                                      /**< (TC_CCR) Register Mask  */


/* -------- TC_CMR : (TC Offset: 0x04) (R/W 32) Channel Mode Register -------- */
#define TC_CMR_Msk                            _U_(0x00000000)                                      /**< (TC_CMR) Register Mask  */

/* CAPTURE mode */
#define TC_CMR_CAPTURE_Msk                    _U_(0x00000000)                                       /**< (TC_CMR_CAPTURE) Register Mask  */

/* WAVEFORM mode */
#define TC_CMR_WAVEFORM_Msk                   _U_(0x00000000)                                       /**< (TC_CMR_WAVEFORM) Register Mask  */


/* -------- TC_SMMR : (TC Offset: 0x08) (R/W 32) Stepper Motor Mode Register -------- */
#define TC_SMMR_GCEN_Pos                      _U_(0)                                               /**< (TC_SMMR) Gray Count Enable Position */
#define TC_SMMR_GCEN_Msk                      (_U_(0x1) << TC_SMMR_GCEN_Pos)                       /**< (TC_SMMR) Gray Count Enable Mask */
#define TC_SMMR_GCEN(value)                   (TC_SMMR_GCEN_Msk & ((value) << TC_SMMR_GCEN_Pos))  
#define TC_SMMR_DOWN_Pos                      _U_(1)                                               /**< (TC_SMMR) Down Count Position */
#define TC_SMMR_DOWN_Msk                      (_U_(0x1) << TC_SMMR_DOWN_Pos)                       /**< (TC_SMMR) Down Count Mask */
#define TC_SMMR_DOWN(value)                   (TC_SMMR_DOWN_Msk & ((value) << TC_SMMR_DOWN_Pos))  
#define TC_SMMR_Msk                           _U_(0x00000003)                                      /**< (TC_SMMR) Register Mask  */


/* -------- TC_RAB : (TC Offset: 0x0C) ( R/ 32) Register AB -------- */
#define TC_RAB_RAB_Pos                        _U_(0)                                               /**< (TC_RAB) Register A or Register B Position */
#define TC_RAB_RAB_Msk                        (_U_(0xFFFFFFFF) << TC_RAB_RAB_Pos)                  /**< (TC_RAB) Register A or Register B Mask */
#define TC_RAB_RAB(value)                     (TC_RAB_RAB_Msk & ((value) << TC_RAB_RAB_Pos))      
#define TC_RAB_Msk                            _U_(0xFFFFFFFF)                                      /**< (TC_RAB) Register Mask  */


/* -------- TC_CV : (TC Offset: 0x10) ( R/ 32) Counter Value -------- */
#define TC_CV_CV_Pos                          _U_(0)                                               /**< (TC_CV) Counter Value Position */
#define TC_CV_CV_Msk                          (_U_(0xFFFFFFFF) << TC_CV_CV_Pos)                    /**< (TC_CV) Counter Value Mask */
#define TC_CV_CV(value)                       (TC_CV_CV_Msk & ((value) << TC_CV_CV_Pos))          
#define TC_CV_Msk                             _U_(0xFFFFFFFF)                                      /**< (TC_CV) Register Mask  */


/* -------- TC_RA : (TC Offset: 0x14) (R/W 32) Register A -------- */
#define TC_RA_RA_Pos                          _U_(0)                                               /**< (TC_RA) Register A Position */
#define TC_RA_RA_Msk                          (_U_(0xFFFFFFFF) << TC_RA_RA_Pos)                    /**< (TC_RA) Register A Mask */
#define TC_RA_RA(value)                       (TC_RA_RA_Msk & ((value) << TC_RA_RA_Pos))          
#define TC_RA_Msk                             _U_(0xFFFFFFFF)                                      /**< (TC_RA) Register Mask  */


/* -------- TC_RB : (TC Offset: 0x18) (R/W 32) Register B -------- */
#define TC_RB_RB_Pos                          _U_(0)                                               /**< (TC_RB) Register B Position */
#define TC_RB_RB_Msk                          (_U_(0xFFFFFFFF) << TC_RB_RB_Pos)                    /**< (TC_RB) Register B Mask */
#define TC_RB_RB(value)                       (TC_RB_RB_Msk & ((value) << TC_RB_RB_Pos))          
#define TC_RB_Msk                             _U_(0xFFFFFFFF)                                      /**< (TC_RB) Register Mask  */


/* -------- TC_RC : (TC Offset: 0x1C) (R/W 32) Register C -------- */
#define TC_RC_RC_Pos                          _U_(0)                                               /**< (TC_RC) Register C Position */
#define TC_RC_RC_Msk                          (_U_(0xFFFFFFFF) << TC_RC_RC_Pos)                    /**< (TC_RC) Register C Mask */
#define TC_RC_RC(value)                       (TC_RC_RC_Msk & ((value) << TC_RC_RC_Pos))          
#define TC_RC_Msk                             _U_(0xFFFFFFFF)                                      /**< (TC_RC) Register Mask  */


/* -------- TC_SR : (TC Offset: 0x20) ( R/ 32) Interrupt Status Register -------- */
#define TC_SR_COVFS_Pos                       _U_(0)                                               /**< (TC_SR) Counter Overflow Status (cleared on read) Position */
#define TC_SR_COVFS_Msk                       (_U_(0x1) << TC_SR_COVFS_Pos)                        /**< (TC_SR) Counter Overflow Status (cleared on read) Mask */
#define TC_SR_COVFS(value)                    (TC_SR_COVFS_Msk & ((value) << TC_SR_COVFS_Pos))    
#define TC_SR_LOVRS_Pos                       _U_(1)                                               /**< (TC_SR) Load Overrun Status (cleared on read) Position */
#define TC_SR_LOVRS_Msk                       (_U_(0x1) << TC_SR_LOVRS_Pos)                        /**< (TC_SR) Load Overrun Status (cleared on read) Mask */
#define TC_SR_LOVRS(value)                    (TC_SR_LOVRS_Msk & ((value) << TC_SR_LOVRS_Pos))    
#define TC_SR_CPAS_Pos                        _U_(2)                                               /**< (TC_SR) RA Compare Status (cleared on read) Position */
#define TC_SR_CPAS_Msk                        (_U_(0x1) << TC_SR_CPAS_Pos)                         /**< (TC_SR) RA Compare Status (cleared on read) Mask */
#define TC_SR_CPAS(value)                     (TC_SR_CPAS_Msk & ((value) << TC_SR_CPAS_Pos))      
#define TC_SR_CPBS_Pos                        _U_(3)                                               /**< (TC_SR) RB Compare Status (cleared on read) Position */
#define TC_SR_CPBS_Msk                        (_U_(0x1) << TC_SR_CPBS_Pos)                         /**< (TC_SR) RB Compare Status (cleared on read) Mask */
#define TC_SR_CPBS(value)                     (TC_SR_CPBS_Msk & ((value) << TC_SR_CPBS_Pos))      
#define TC_SR_CPCS_Pos                        _U_(4)                                               /**< (TC_SR) RC Compare Status (cleared on read) Position */
#define TC_SR_CPCS_Msk                        (_U_(0x1) << TC_SR_CPCS_Pos)                         /**< (TC_SR) RC Compare Status (cleared on read) Mask */
#define TC_SR_CPCS(value)                     (TC_SR_CPCS_Msk & ((value) << TC_SR_CPCS_Pos))      
#define TC_SR_LDRAS_Pos                       _U_(5)                                               /**< (TC_SR) RA Loading Status (cleared on read) Position */
#define TC_SR_LDRAS_Msk                       (_U_(0x1) << TC_SR_LDRAS_Pos)                        /**< (TC_SR) RA Loading Status (cleared on read) Mask */
#define TC_SR_LDRAS(value)                    (TC_SR_LDRAS_Msk & ((value) << TC_SR_LDRAS_Pos))    
#define TC_SR_LDRBS_Pos                       _U_(6)                                               /**< (TC_SR) RB Loading Status (cleared on read) Position */
#define TC_SR_LDRBS_Msk                       (_U_(0x1) << TC_SR_LDRBS_Pos)                        /**< (TC_SR) RB Loading Status (cleared on read) Mask */
#define TC_SR_LDRBS(value)                    (TC_SR_LDRBS_Msk & ((value) << TC_SR_LDRBS_Pos))    
#define TC_SR_ETRGS_Pos                       _U_(7)                                               /**< (TC_SR) External Trigger Status (cleared on read) Position */
#define TC_SR_ETRGS_Msk                       (_U_(0x1) << TC_SR_ETRGS_Pos)                        /**< (TC_SR) External Trigger Status (cleared on read) Mask */
#define TC_SR_ETRGS(value)                    (TC_SR_ETRGS_Msk & ((value) << TC_SR_ETRGS_Pos))    
#define TC_SR_SECE_Pos                        _U_(10)                                              /**< (TC_SR) Security and/or Safety Event (cleared on read) Position */
#define TC_SR_SECE_Msk                        (_U_(0x1) << TC_SR_SECE_Pos)                         /**< (TC_SR) Security and/or Safety Event (cleared on read) Mask */
#define TC_SR_SECE(value)                     (TC_SR_SECE_Msk & ((value) << TC_SR_SECE_Pos))      
#define TC_SR_CLKSTA_Pos                      _U_(16)                                              /**< (TC_SR) Clock Enabling Status Position */
#define TC_SR_CLKSTA_Msk                      (_U_(0x1) << TC_SR_CLKSTA_Pos)                       /**< (TC_SR) Clock Enabling Status Mask */
#define TC_SR_CLKSTA(value)                   (TC_SR_CLKSTA_Msk & ((value) << TC_SR_CLKSTA_Pos))  
#define TC_SR_MTIOA_Pos                       _U_(17)                                              /**< (TC_SR) TIOAx Mirror Position */
#define TC_SR_MTIOA_Msk                       (_U_(0x1) << TC_SR_MTIOA_Pos)                        /**< (TC_SR) TIOAx Mirror Mask */
#define TC_SR_MTIOA(value)                    (TC_SR_MTIOA_Msk & ((value) << TC_SR_MTIOA_Pos))    
#define TC_SR_MTIOB_Pos                       _U_(18)                                              /**< (TC_SR) TIOBx Mirror Position */
#define TC_SR_MTIOB_Msk                       (_U_(0x1) << TC_SR_MTIOB_Pos)                        /**< (TC_SR) TIOBx Mirror Mask */
#define TC_SR_MTIOB(value)                    (TC_SR_MTIOB_Msk & ((value) << TC_SR_MTIOB_Pos))    
#define TC_SR_Msk                             _U_(0x000704FF)                                      /**< (TC_SR) Register Mask  */


/* -------- TC_IER : (TC Offset: 0x24) ( /W 32) Interrupt Enable Register -------- */
#define TC_IER_COVFS_Pos                      _U_(0)                                               /**< (TC_IER) Counter Overflow Position */
#define TC_IER_COVFS_Msk                      (_U_(0x1) << TC_IER_COVFS_Pos)                       /**< (TC_IER) Counter Overflow Mask */
#define TC_IER_COVFS(value)                   (TC_IER_COVFS_Msk & ((value) << TC_IER_COVFS_Pos))  
#define TC_IER_LOVRS_Pos                      _U_(1)                                               /**< (TC_IER) Load Overrun Position */
#define TC_IER_LOVRS_Msk                      (_U_(0x1) << TC_IER_LOVRS_Pos)                       /**< (TC_IER) Load Overrun Mask */
#define TC_IER_LOVRS(value)                   (TC_IER_LOVRS_Msk & ((value) << TC_IER_LOVRS_Pos))  
#define TC_IER_CPAS_Pos                       _U_(2)                                               /**< (TC_IER) RA Compare Position */
#define TC_IER_CPAS_Msk                       (_U_(0x1) << TC_IER_CPAS_Pos)                        /**< (TC_IER) RA Compare Mask */
#define TC_IER_CPAS(value)                    (TC_IER_CPAS_Msk & ((value) << TC_IER_CPAS_Pos))    
#define TC_IER_CPBS_Pos                       _U_(3)                                               /**< (TC_IER) RB Compare Position */
#define TC_IER_CPBS_Msk                       (_U_(0x1) << TC_IER_CPBS_Pos)                        /**< (TC_IER) RB Compare Mask */
#define TC_IER_CPBS(value)                    (TC_IER_CPBS_Msk & ((value) << TC_IER_CPBS_Pos))    
#define TC_IER_CPCS_Pos                       _U_(4)                                               /**< (TC_IER) RC Compare Position */
#define TC_IER_CPCS_Msk                       (_U_(0x1) << TC_IER_CPCS_Pos)                        /**< (TC_IER) RC Compare Mask */
#define TC_IER_CPCS(value)                    (TC_IER_CPCS_Msk & ((value) << TC_IER_CPCS_Pos))    
#define TC_IER_LDRAS_Pos                      _U_(5)                                               /**< (TC_IER) RA Loading Position */
#define TC_IER_LDRAS_Msk                      (_U_(0x1) << TC_IER_LDRAS_Pos)                       /**< (TC_IER) RA Loading Mask */
#define TC_IER_LDRAS(value)                   (TC_IER_LDRAS_Msk & ((value) << TC_IER_LDRAS_Pos))  
#define TC_IER_LDRBS_Pos                      _U_(6)                                               /**< (TC_IER) RB Loading Position */
#define TC_IER_LDRBS_Msk                      (_U_(0x1) << TC_IER_LDRBS_Pos)                       /**< (TC_IER) RB Loading Mask */
#define TC_IER_LDRBS(value)                   (TC_IER_LDRBS_Msk & ((value) << TC_IER_LDRBS_Pos))  
#define TC_IER_ETRGS_Pos                      _U_(7)                                               /**< (TC_IER) External Trigger Position */
#define TC_IER_ETRGS_Msk                      (_U_(0x1) << TC_IER_ETRGS_Pos)                       /**< (TC_IER) External Trigger Mask */
#define TC_IER_ETRGS(value)                   (TC_IER_ETRGS_Msk & ((value) << TC_IER_ETRGS_Pos))  
#define TC_IER_SECE_Pos                       _U_(10)                                              /**< (TC_IER) Security and/or Safety Event Interrupt Enable Position */
#define TC_IER_SECE_Msk                       (_U_(0x1) << TC_IER_SECE_Pos)                        /**< (TC_IER) Security and/or Safety Event Interrupt Enable Mask */
#define TC_IER_SECE(value)                    (TC_IER_SECE_Msk & ((value) << TC_IER_SECE_Pos))    
#define TC_IER_Msk                            _U_(0x000004FF)                                      /**< (TC_IER) Register Mask  */


/* -------- TC_IDR : (TC Offset: 0x28) ( /W 32) Interrupt Disable Register -------- */
#define TC_IDR_COVFS_Pos                      _U_(0)                                               /**< (TC_IDR) Counter Overflow Position */
#define TC_IDR_COVFS_Msk                      (_U_(0x1) << TC_IDR_COVFS_Pos)                       /**< (TC_IDR) Counter Overflow Mask */
#define TC_IDR_COVFS(value)                   (TC_IDR_COVFS_Msk & ((value) << TC_IDR_COVFS_Pos))  
#define TC_IDR_LOVRS_Pos                      _U_(1)                                               /**< (TC_IDR) Load Overrun Position */
#define TC_IDR_LOVRS_Msk                      (_U_(0x1) << TC_IDR_LOVRS_Pos)                       /**< (TC_IDR) Load Overrun Mask */
#define TC_IDR_LOVRS(value)                   (TC_IDR_LOVRS_Msk & ((value) << TC_IDR_LOVRS_Pos))  
#define TC_IDR_CPAS_Pos                       _U_(2)                                               /**< (TC_IDR) RA Compare Position */
#define TC_IDR_CPAS_Msk                       (_U_(0x1) << TC_IDR_CPAS_Pos)                        /**< (TC_IDR) RA Compare Mask */
#define TC_IDR_CPAS(value)                    (TC_IDR_CPAS_Msk & ((value) << TC_IDR_CPAS_Pos))    
#define TC_IDR_CPBS_Pos                       _U_(3)                                               /**< (TC_IDR) RB Compare Position */
#define TC_IDR_CPBS_Msk                       (_U_(0x1) << TC_IDR_CPBS_Pos)                        /**< (TC_IDR) RB Compare Mask */
#define TC_IDR_CPBS(value)                    (TC_IDR_CPBS_Msk & ((value) << TC_IDR_CPBS_Pos))    
#define TC_IDR_CPCS_Pos                       _U_(4)                                               /**< (TC_IDR) RC Compare Position */
#define TC_IDR_CPCS_Msk                       (_U_(0x1) << TC_IDR_CPCS_Pos)                        /**< (TC_IDR) RC Compare Mask */
#define TC_IDR_CPCS(value)                    (TC_IDR_CPCS_Msk & ((value) << TC_IDR_CPCS_Pos))    
#define TC_IDR_LDRAS_Pos                      _U_(5)                                               /**< (TC_IDR) RA Loading Position */
#define TC_IDR_LDRAS_Msk                      (_U_(0x1) << TC_IDR_LDRAS_Pos)                       /**< (TC_IDR) RA Loading Mask */
#define TC_IDR_LDRAS(value)                   (TC_IDR_LDRAS_Msk & ((value) << TC_IDR_LDRAS_Pos))  
#define TC_IDR_LDRBS_Pos                      _U_(6)                                               /**< (TC_IDR) RB Loading Position */
#define TC_IDR_LDRBS_Msk                      (_U_(0x1) << TC_IDR_LDRBS_Pos)                       /**< (TC_IDR) RB Loading Mask */
#define TC_IDR_LDRBS(value)                   (TC_IDR_LDRBS_Msk & ((value) << TC_IDR_LDRBS_Pos))  
#define TC_IDR_ETRGS_Pos                      _U_(7)                                               /**< (TC_IDR) External Trigger Position */
#define TC_IDR_ETRGS_Msk                      (_U_(0x1) << TC_IDR_ETRGS_Pos)                       /**< (TC_IDR) External Trigger Mask */
#define TC_IDR_ETRGS(value)                   (TC_IDR_ETRGS_Msk & ((value) << TC_IDR_ETRGS_Pos))  
#define TC_IDR_SECE_Pos                       _U_(10)                                              /**< (TC_IDR) Security and/or Safety Event Interrupt Disable Position */
#define TC_IDR_SECE_Msk                       (_U_(0x1) << TC_IDR_SECE_Pos)                        /**< (TC_IDR) Security and/or Safety Event Interrupt Disable Mask */
#define TC_IDR_SECE(value)                    (TC_IDR_SECE_Msk & ((value) << TC_IDR_SECE_Pos))    
#define TC_IDR_Msk                            _U_(0x000004FF)                                      /**< (TC_IDR) Register Mask  */


/* -------- TC_IMR : (TC Offset: 0x2C) ( R/ 32) Interrupt Mask Register -------- */
#define TC_IMR_COVFS_Pos                      _U_(0)                                               /**< (TC_IMR) Counter Overflow Position */
#define TC_IMR_COVFS_Msk                      (_U_(0x1) << TC_IMR_COVFS_Pos)                       /**< (TC_IMR) Counter Overflow Mask */
#define TC_IMR_COVFS(value)                   (TC_IMR_COVFS_Msk & ((value) << TC_IMR_COVFS_Pos))  
#define TC_IMR_LOVRS_Pos                      _U_(1)                                               /**< (TC_IMR) Load Overrun Position */
#define TC_IMR_LOVRS_Msk                      (_U_(0x1) << TC_IMR_LOVRS_Pos)                       /**< (TC_IMR) Load Overrun Mask */
#define TC_IMR_LOVRS(value)                   (TC_IMR_LOVRS_Msk & ((value) << TC_IMR_LOVRS_Pos))  
#define TC_IMR_CPAS_Pos                       _U_(2)                                               /**< (TC_IMR) RA Compare Position */
#define TC_IMR_CPAS_Msk                       (_U_(0x1) << TC_IMR_CPAS_Pos)                        /**< (TC_IMR) RA Compare Mask */
#define TC_IMR_CPAS(value)                    (TC_IMR_CPAS_Msk & ((value) << TC_IMR_CPAS_Pos))    
#define TC_IMR_CPBS_Pos                       _U_(3)                                               /**< (TC_IMR) RB Compare Position */
#define TC_IMR_CPBS_Msk                       (_U_(0x1) << TC_IMR_CPBS_Pos)                        /**< (TC_IMR) RB Compare Mask */
#define TC_IMR_CPBS(value)                    (TC_IMR_CPBS_Msk & ((value) << TC_IMR_CPBS_Pos))    
#define TC_IMR_CPCS_Pos                       _U_(4)                                               /**< (TC_IMR) RC Compare Position */
#define TC_IMR_CPCS_Msk                       (_U_(0x1) << TC_IMR_CPCS_Pos)                        /**< (TC_IMR) RC Compare Mask */
#define TC_IMR_CPCS(value)                    (TC_IMR_CPCS_Msk & ((value) << TC_IMR_CPCS_Pos))    
#define TC_IMR_LDRAS_Pos                      _U_(5)                                               /**< (TC_IMR) RA Loading Position */
#define TC_IMR_LDRAS_Msk                      (_U_(0x1) << TC_IMR_LDRAS_Pos)                       /**< (TC_IMR) RA Loading Mask */
#define TC_IMR_LDRAS(value)                   (TC_IMR_LDRAS_Msk & ((value) << TC_IMR_LDRAS_Pos))  
#define TC_IMR_LDRBS_Pos                      _U_(6)                                               /**< (TC_IMR) RB Loading Position */
#define TC_IMR_LDRBS_Msk                      (_U_(0x1) << TC_IMR_LDRBS_Pos)                       /**< (TC_IMR) RB Loading Mask */
#define TC_IMR_LDRBS(value)                   (TC_IMR_LDRBS_Msk & ((value) << TC_IMR_LDRBS_Pos))  
#define TC_IMR_ETRGS_Pos                      _U_(7)                                               /**< (TC_IMR) External Trigger Position */
#define TC_IMR_ETRGS_Msk                      (_U_(0x1) << TC_IMR_ETRGS_Pos)                       /**< (TC_IMR) External Trigger Mask */
#define TC_IMR_ETRGS(value)                   (TC_IMR_ETRGS_Msk & ((value) << TC_IMR_ETRGS_Pos))  
#define TC_IMR_SECE_Pos                       _U_(10)                                              /**< (TC_IMR) Security and/or Safety Event Interrupt Mask Position */
#define TC_IMR_SECE_Msk                       (_U_(0x1) << TC_IMR_SECE_Pos)                        /**< (TC_IMR) Security and/or Safety Event Interrupt Mask Mask */
#define TC_IMR_SECE(value)                    (TC_IMR_SECE_Msk & ((value) << TC_IMR_SECE_Pos))    
#define TC_IMR_Msk                            _U_(0x000004FF)                                      /**< (TC_IMR) Register Mask  */


/* -------- TC_EMR : (TC Offset: 0x30) (R/W 32) Extended Mode Register -------- */
#define TC_EMR_TRIGSRCA_Pos                   _U_(0)                                               /**< (TC_EMR) Trigger Source for Input A Position */
#define TC_EMR_TRIGSRCA_Msk                   (_U_(0x3) << TC_EMR_TRIGSRCA_Pos)                    /**< (TC_EMR) Trigger Source for Input A Mask */
#define TC_EMR_TRIGSRCA(value)                (TC_EMR_TRIGSRCA_Msk & ((value) << TC_EMR_TRIGSRCA_Pos))
#define   TC_EMR_TRIGSRCA_EXTERNAL_TIOAx_Val  _U_(0x0)                                             /**< (TC_EMR) The trigger/capture input A is driven by external pin TIOAx  */
#define   TC_EMR_TRIGSRCA_PWMx_Val            _U_(0x1)                                             /**< (TC_EMR) The trigger/capture input A is driven internally by PWMx  */
#define TC_EMR_TRIGSRCA_EXTERNAL_TIOAx        (TC_EMR_TRIGSRCA_EXTERNAL_TIOAx_Val << TC_EMR_TRIGSRCA_Pos) /**< (TC_EMR) The trigger/capture input A is driven by external pin TIOAx Position  */
#define TC_EMR_TRIGSRCA_PWMx                  (TC_EMR_TRIGSRCA_PWMx_Val << TC_EMR_TRIGSRCA_Pos)    /**< (TC_EMR) The trigger/capture input A is driven internally by PWMx Position  */
#define TC_EMR_TRIGSRCB_Pos                   _U_(4)                                               /**< (TC_EMR) Trigger Source for Input B Position */
#define TC_EMR_TRIGSRCB_Msk                   (_U_(0x3) << TC_EMR_TRIGSRCB_Pos)                    /**< (TC_EMR) Trigger Source for Input B Mask */
#define TC_EMR_TRIGSRCB(value)                (TC_EMR_TRIGSRCB_Msk & ((value) << TC_EMR_TRIGSRCB_Pos))
#define   TC_EMR_TRIGSRCB_EXTERNAL_TIOBx_Val  _U_(0x0)                                             /**< (TC_EMR) The trigger/capture input B is driven by external pin TIOBx  */
#define   TC_EMR_TRIGSRCB_PWMx_Val            _U_(0x1)                                             /**< (TC_EMR) The trigger/capture input B is driven internally by the comparator output (see Figure 7-16) of the PWMx.  */
#define TC_EMR_TRIGSRCB_EXTERNAL_TIOBx        (TC_EMR_TRIGSRCB_EXTERNAL_TIOBx_Val << TC_EMR_TRIGSRCB_Pos) /**< (TC_EMR) The trigger/capture input B is driven by external pin TIOBx Position  */
#define TC_EMR_TRIGSRCB_PWMx                  (TC_EMR_TRIGSRCB_PWMx_Val << TC_EMR_TRIGSRCB_Pos)    /**< (TC_EMR) The trigger/capture input B is driven internally by the comparator output (see Figure 7-16) of the PWMx. Position  */
#define TC_EMR_NODIVCLK_Pos                   _U_(8)                                               /**< (TC_EMR) No Divided Clock Position */
#define TC_EMR_NODIVCLK_Msk                   (_U_(0x1) << TC_EMR_NODIVCLK_Pos)                    /**< (TC_EMR) No Divided Clock Mask */
#define TC_EMR_NODIVCLK(value)                (TC_EMR_NODIVCLK_Msk & ((value) << TC_EMR_NODIVCLK_Pos))
#define TC_EMR_Msk                            _U_(0x00000133)                                      /**< (TC_EMR) Register Mask  */


/* -------- TC_CSR : (TC Offset: 0x34) ( R/ 32) Channel Status Register -------- */
#define TC_CSR_CLKSTA_Pos                     _U_(16)                                              /**< (TC_CSR) Clock Enabling Status Position */
#define TC_CSR_CLKSTA_Msk                     (_U_(0x1) << TC_CSR_CLKSTA_Pos)                      /**< (TC_CSR) Clock Enabling Status Mask */
#define TC_CSR_CLKSTA(value)                  (TC_CSR_CLKSTA_Msk & ((value) << TC_CSR_CLKSTA_Pos))
#define TC_CSR_MTIOA_Pos                      _U_(17)                                              /**< (TC_CSR) TIOAx Mirror Position */
#define TC_CSR_MTIOA_Msk                      (_U_(0x1) << TC_CSR_MTIOA_Pos)                       /**< (TC_CSR) TIOAx Mirror Mask */
#define TC_CSR_MTIOA(value)                   (TC_CSR_MTIOA_Msk & ((value) << TC_CSR_MTIOA_Pos))  
#define TC_CSR_MTIOB_Pos                      _U_(18)                                              /**< (TC_CSR) TIOBx Mirror Position */
#define TC_CSR_MTIOB_Msk                      (_U_(0x1) << TC_CSR_MTIOB_Pos)                       /**< (TC_CSR) TIOBx Mirror Mask */
#define TC_CSR_MTIOB(value)                   (TC_CSR_MTIOB_Msk & ((value) << TC_CSR_MTIOB_Pos))  
#define TC_CSR_Msk                            _U_(0x00070000)                                      /**< (TC_CSR) Register Mask  */


/* -------- TC_SSR : (TC Offset: 0x38) ( R/ 32) Safety Status Register -------- */
#define TC_SSR_WPVS_Pos                       _U_(0)                                               /**< (TC_SSR) Write Protection Violation Status (cleared on read) Position */
#define TC_SSR_WPVS_Msk                       (_U_(0x1) << TC_SSR_WPVS_Pos)                        /**< (TC_SSR) Write Protection Violation Status (cleared on read) Mask */
#define TC_SSR_WPVS(value)                    (TC_SSR_WPVS_Msk & ((value) << TC_SSR_WPVS_Pos))    
#define TC_SSR_CGD_Pos                        _U_(1)                                               /**< (TC_SSR) Clock Glitch Detected (cleared on read) Position */
#define TC_SSR_CGD_Msk                        (_U_(0x1) << TC_SSR_CGD_Pos)                         /**< (TC_SSR) Clock Glitch Detected (cleared on read) Mask */
#define TC_SSR_CGD(value)                     (TC_SSR_CGD_Msk & ((value) << TC_SSR_CGD_Pos))      
#define TC_SSR_SEQE_Pos                       _U_(2)                                               /**< (TC_SSR) Internal Sequencer Error (cleared on read) Position */
#define TC_SSR_SEQE_Msk                       (_U_(0x1) << TC_SSR_SEQE_Pos)                        /**< (TC_SSR) Internal Sequencer Error (cleared on read) Mask */
#define TC_SSR_SEQE(value)                    (TC_SSR_SEQE_Msk & ((value) << TC_SSR_SEQE_Pos))    
#define TC_SSR_SWE_Pos                        _U_(3)                                               /**< (TC_SSR) Software Control Error (cleared on read) Position */
#define TC_SSR_SWE_Msk                        (_U_(0x1) << TC_SSR_SWE_Pos)                         /**< (TC_SSR) Software Control Error (cleared on read) Mask */
#define TC_SSR_SWE(value)                     (TC_SSR_SWE_Msk & ((value) << TC_SSR_SWE_Pos))      
#define TC_SSR_WPVSRC_Pos                     _U_(8)                                               /**< (TC_SSR) Write Protection Violation Source (cleared on read) Position */
#define TC_SSR_WPVSRC_Msk                     (_U_(0xFFFF) << TC_SSR_WPVSRC_Pos)                   /**< (TC_SSR) Write Protection Violation Source (cleared on read) Mask */
#define TC_SSR_WPVSRC(value)                  (TC_SSR_WPVSRC_Msk & ((value) << TC_SSR_WPVSRC_Pos))
#define TC_SSR_SWETYP_Pos                     _U_(24)                                              /**< (TC_SSR) Software Error Type (cleared on read) Position */
#define TC_SSR_SWETYP_Msk                     (_U_(0xF) << TC_SSR_SWETYP_Pos)                      /**< (TC_SSR) Software Error Type (cleared on read) Mask */
#define TC_SSR_SWETYP(value)                  (TC_SSR_SWETYP_Msk & ((value) << TC_SSR_SWETYP_Pos))
#define   TC_SSR_SWETYP_READ_WO_Val           _U_(0x0)                                             /**< (TC_SSR) TC Channel x is enabled and a write-only register has been read (Warning).  */
#define   TC_SSR_SWETYP_WRITE_RO_Val          _U_(0x1)                                             /**< (TC_SSR) TC Channel x is enabled and a write access has been performed on a read-only register (Warning).  */
#define   TC_SSR_SWETYP_UNDEF_RW_Val          _U_(0x2)                                             /**< (TC_SSR) Access to an undefined address of the TC (Warning).  */
#define   TC_SSR_SWETYP_W_RARB_CAPT_Val       _U_(0x3)                                             /**< (TC_SSR) TC_RAx or TC_RBx are written while channel is enabled and configured in capture mode (Error).  */
#define TC_SSR_SWETYP_READ_WO                 (TC_SSR_SWETYP_READ_WO_Val << TC_SSR_SWETYP_Pos)     /**< (TC_SSR) TC Channel x is enabled and a write-only register has been read (Warning). Position  */
#define TC_SSR_SWETYP_WRITE_RO                (TC_SSR_SWETYP_WRITE_RO_Val << TC_SSR_SWETYP_Pos)    /**< (TC_SSR) TC Channel x is enabled and a write access has been performed on a read-only register (Warning). Position  */
#define TC_SSR_SWETYP_UNDEF_RW                (TC_SSR_SWETYP_UNDEF_RW_Val << TC_SSR_SWETYP_Pos)    /**< (TC_SSR) Access to an undefined address of the TC (Warning). Position  */
#define TC_SSR_SWETYP_W_RARB_CAPT             (TC_SSR_SWETYP_W_RARB_CAPT_Val << TC_SSR_SWETYP_Pos) /**< (TC_SSR) TC_RAx or TC_RBx are written while channel is enabled and configured in capture mode (Error). Position  */
#define TC_SSR_ECLASS_Pos                     _U_(31)                                              /**< (TC_SSR) Software Error Class Position */
#define TC_SSR_ECLASS_Msk                     (_U_(0x1) << TC_SSR_ECLASS_Pos)                      /**< (TC_SSR) Software Error Class Mask */
#define TC_SSR_ECLASS(value)                  (TC_SSR_ECLASS_Msk & ((value) << TC_SSR_ECLASS_Pos))
#define   TC_SSR_ECLASS_WARNING_Val           _U_(0x0)                                             /**< (TC_SSR) An abnormal access that does not have any impact.  */
#define   TC_SSR_ECLASS_ERROR_Val             _U_(0x1)                                             /**< (TC_SSR) An abnormal access that may have an impact.  */
#define TC_SSR_ECLASS_WARNING                 (TC_SSR_ECLASS_WARNING_Val << TC_SSR_ECLASS_Pos)     /**< (TC_SSR) An abnormal access that does not have any impact. Position  */
#define TC_SSR_ECLASS_ERROR                   (TC_SSR_ECLASS_ERROR_Val << TC_SSR_ECLASS_Pos)       /**< (TC_SSR) An abnormal access that may have an impact. Position  */
#define TC_SSR_Msk                            _U_(0x8FFFFF0F)                                      /**< (TC_SSR) Register Mask  */


/* -------- TC_BCR : (TC Offset: 0xC0) ( /W 32) Block Control Register -------- */
#define TC_BCR_SYNC_Pos                       _U_(0)                                               /**< (TC_BCR) Synchro Command Position */
#define TC_BCR_SYNC_Msk                       (_U_(0x1) << TC_BCR_SYNC_Pos)                        /**< (TC_BCR) Synchro Command Mask */
#define TC_BCR_SYNC(value)                    (TC_BCR_SYNC_Msk & ((value) << TC_BCR_SYNC_Pos))    
#define TC_BCR_Msk                            _U_(0x00000001)                                      /**< (TC_BCR) Register Mask  */


/* -------- TC_BMR : (TC Offset: 0xC4) (R/W 32) Block Mode Register -------- */
#define TC_BMR_TC0XC0S_Pos                    _U_(0)                                               /**< (TC_BMR) External Clock Signal 0 Selection Position */
#define TC_BMR_TC0XC0S_Msk                    (_U_(0x3) << TC_BMR_TC0XC0S_Pos)                     /**< (TC_BMR) External Clock Signal 0 Selection Mask */
#define TC_BMR_TC0XC0S(value)                 (TC_BMR_TC0XC0S_Msk & ((value) << TC_BMR_TC0XC0S_Pos))
#define   TC_BMR_TC0XC0S_TCLK0_Val            _U_(0x0)                                             /**< (TC_BMR) Signal connected to XC0: TCLK0  */
#define   TC_BMR_TC0XC0S_TIOA1_Val            _U_(0x2)                                             /**< (TC_BMR) Signal connected to XC0: TIOA1  */
#define   TC_BMR_TC0XC0S_TIOA2_Val            _U_(0x3)                                             /**< (TC_BMR) Signal connected to XC0: TIOA2  */
#define TC_BMR_TC0XC0S_TCLK0                  (TC_BMR_TC0XC0S_TCLK0_Val << TC_BMR_TC0XC0S_Pos)     /**< (TC_BMR) Signal connected to XC0: TCLK0 Position  */
#define TC_BMR_TC0XC0S_TIOA1                  (TC_BMR_TC0XC0S_TIOA1_Val << TC_BMR_TC0XC0S_Pos)     /**< (TC_BMR) Signal connected to XC0: TIOA1 Position  */
#define TC_BMR_TC0XC0S_TIOA2                  (TC_BMR_TC0XC0S_TIOA2_Val << TC_BMR_TC0XC0S_Pos)     /**< (TC_BMR) Signal connected to XC0: TIOA2 Position  */
#define TC_BMR_TC1XC1S_Pos                    _U_(2)                                               /**< (TC_BMR) External Clock Signal 1 Selection Position */
#define TC_BMR_TC1XC1S_Msk                    (_U_(0x3) << TC_BMR_TC1XC1S_Pos)                     /**< (TC_BMR) External Clock Signal 1 Selection Mask */
#define TC_BMR_TC1XC1S(value)                 (TC_BMR_TC1XC1S_Msk & ((value) << TC_BMR_TC1XC1S_Pos))
#define   TC_BMR_TC1XC1S_TCLK1_Val            _U_(0x0)                                             /**< (TC_BMR) Signal connected to XC1: TCLK1  */
#define   TC_BMR_TC1XC1S_TIOA0_Val            _U_(0x2)                                             /**< (TC_BMR) Signal connected to XC1: TIOA0  */
#define   TC_BMR_TC1XC1S_TIOA2_Val            _U_(0x3)                                             /**< (TC_BMR) Signal connected to XC1: TIOA2  */
#define TC_BMR_TC1XC1S_TCLK1                  (TC_BMR_TC1XC1S_TCLK1_Val << TC_BMR_TC1XC1S_Pos)     /**< (TC_BMR) Signal connected to XC1: TCLK1 Position  */
#define TC_BMR_TC1XC1S_TIOA0                  (TC_BMR_TC1XC1S_TIOA0_Val << TC_BMR_TC1XC1S_Pos)     /**< (TC_BMR) Signal connected to XC1: TIOA0 Position  */
#define TC_BMR_TC1XC1S_TIOA2                  (TC_BMR_TC1XC1S_TIOA2_Val << TC_BMR_TC1XC1S_Pos)     /**< (TC_BMR) Signal connected to XC1: TIOA2 Position  */
#define TC_BMR_TC2XC2S_Pos                    _U_(4)                                               /**< (TC_BMR) External Clock Signal 2 Selection Position */
#define TC_BMR_TC2XC2S_Msk                    (_U_(0x3) << TC_BMR_TC2XC2S_Pos)                     /**< (TC_BMR) External Clock Signal 2 Selection Mask */
#define TC_BMR_TC2XC2S(value)                 (TC_BMR_TC2XC2S_Msk & ((value) << TC_BMR_TC2XC2S_Pos))
#define   TC_BMR_TC2XC2S_TCLK2_Val            _U_(0x0)                                             /**< (TC_BMR) Signal connected to XC2: TCLK2  */
#define   TC_BMR_TC2XC2S_TIOA0_Val            _U_(0x2)                                             /**< (TC_BMR) Signal connected to XC2: TIOA0  */
#define   TC_BMR_TC2XC2S_TIOA1_Val            _U_(0x3)                                             /**< (TC_BMR) Signal connected to XC2: TIOA1  */
#define TC_BMR_TC2XC2S_TCLK2                  (TC_BMR_TC2XC2S_TCLK2_Val << TC_BMR_TC2XC2S_Pos)     /**< (TC_BMR) Signal connected to XC2: TCLK2 Position  */
#define TC_BMR_TC2XC2S_TIOA0                  (TC_BMR_TC2XC2S_TIOA0_Val << TC_BMR_TC2XC2S_Pos)     /**< (TC_BMR) Signal connected to XC2: TIOA0 Position  */
#define TC_BMR_TC2XC2S_TIOA1                  (TC_BMR_TC2XC2S_TIOA1_Val << TC_BMR_TC2XC2S_Pos)     /**< (TC_BMR) Signal connected to XC2: TIOA1 Position  */
#define TC_BMR_QDEN_Pos                       _U_(8)                                               /**< (TC_BMR) Quadrature Decoder Enabled Position */
#define TC_BMR_QDEN_Msk                       (_U_(0x1) << TC_BMR_QDEN_Pos)                        /**< (TC_BMR) Quadrature Decoder Enabled Mask */
#define TC_BMR_QDEN(value)                    (TC_BMR_QDEN_Msk & ((value) << TC_BMR_QDEN_Pos))    
#define TC_BMR_POSEN_Pos                      _U_(9)                                               /**< (TC_BMR) Position Enabled Position */
#define TC_BMR_POSEN_Msk                      (_U_(0x1) << TC_BMR_POSEN_Pos)                       /**< (TC_BMR) Position Enabled Mask */
#define TC_BMR_POSEN(value)                   (TC_BMR_POSEN_Msk & ((value) << TC_BMR_POSEN_Pos))  
#define TC_BMR_SPEEDEN_Pos                    _U_(10)                                              /**< (TC_BMR) Speed Enabled Position */
#define TC_BMR_SPEEDEN_Msk                    (_U_(0x1) << TC_BMR_SPEEDEN_Pos)                     /**< (TC_BMR) Speed Enabled Mask */
#define TC_BMR_SPEEDEN(value)                 (TC_BMR_SPEEDEN_Msk & ((value) << TC_BMR_SPEEDEN_Pos))
#define TC_BMR_QDTRANS_Pos                    _U_(11)                                              /**< (TC_BMR) Quadrature Decoding Transparent Position */
#define TC_BMR_QDTRANS_Msk                    (_U_(0x1) << TC_BMR_QDTRANS_Pos)                     /**< (TC_BMR) Quadrature Decoding Transparent Mask */
#define TC_BMR_QDTRANS(value)                 (TC_BMR_QDTRANS_Msk & ((value) << TC_BMR_QDTRANS_Pos))
#define TC_BMR_EDGPHA_Pos                     _U_(12)                                              /**< (TC_BMR) Edge on PHA Count Mode Position */
#define TC_BMR_EDGPHA_Msk                     (_U_(0x1) << TC_BMR_EDGPHA_Pos)                      /**< (TC_BMR) Edge on PHA Count Mode Mask */
#define TC_BMR_EDGPHA(value)                  (TC_BMR_EDGPHA_Msk & ((value) << TC_BMR_EDGPHA_Pos))
#define TC_BMR_INVA_Pos                       _U_(13)                                              /**< (TC_BMR) Inverted PHA Position */
#define TC_BMR_INVA_Msk                       (_U_(0x1) << TC_BMR_INVA_Pos)                        /**< (TC_BMR) Inverted PHA Mask */
#define TC_BMR_INVA(value)                    (TC_BMR_INVA_Msk & ((value) << TC_BMR_INVA_Pos))    
#define TC_BMR_INVB_Pos                       _U_(14)                                              /**< (TC_BMR) Inverted PHB Position */
#define TC_BMR_INVB_Msk                       (_U_(0x1) << TC_BMR_INVB_Pos)                        /**< (TC_BMR) Inverted PHB Mask */
#define TC_BMR_INVB(value)                    (TC_BMR_INVB_Msk & ((value) << TC_BMR_INVB_Pos))    
#define TC_BMR_INVIDX_Pos                     _U_(15)                                              /**< (TC_BMR) Inverted Index Position */
#define TC_BMR_INVIDX_Msk                     (_U_(0x1) << TC_BMR_INVIDX_Pos)                      /**< (TC_BMR) Inverted Index Mask */
#define TC_BMR_INVIDX(value)                  (TC_BMR_INVIDX_Msk & ((value) << TC_BMR_INVIDX_Pos))
#define TC_BMR_SWAP_Pos                       _U_(16)                                              /**< (TC_BMR) Swap PHA and PHB Position */
#define TC_BMR_SWAP_Msk                       (_U_(0x1) << TC_BMR_SWAP_Pos)                        /**< (TC_BMR) Swap PHA and PHB Mask */
#define TC_BMR_SWAP(value)                    (TC_BMR_SWAP_Msk & ((value) << TC_BMR_SWAP_Pos))    
#define TC_BMR_IDXPHB_Pos                     _U_(17)                                              /**< (TC_BMR) Index Pin is PHB Pin Position */
#define TC_BMR_IDXPHB_Msk                     (_U_(0x1) << TC_BMR_IDXPHB_Pos)                      /**< (TC_BMR) Index Pin is PHB Pin Mask */
#define TC_BMR_IDXPHB(value)                  (TC_BMR_IDXPHB_Msk & ((value) << TC_BMR_IDXPHB_Pos))
#define TC_BMR_MAXFILT_Pos                    _U_(20)                                              /**< (TC_BMR) Maximum Filter Position */
#define TC_BMR_MAXFILT_Msk                    (_U_(0x3F) << TC_BMR_MAXFILT_Pos)                    /**< (TC_BMR) Maximum Filter Mask */
#define TC_BMR_MAXFILT(value)                 (TC_BMR_MAXFILT_Msk & ((value) << TC_BMR_MAXFILT_Pos))
#define TC_BMR_Msk                            _U_(0x03F3FF3F)                                      /**< (TC_BMR) Register Mask  */


/* -------- TC_QIER : (TC Offset: 0xC8) ( /W 32) QDEC Interrupt Enable Register -------- */
#define TC_QIER_IDX_Pos                       _U_(0)                                               /**< (TC_QIER) Index Position */
#define TC_QIER_IDX_Msk                       (_U_(0x1) << TC_QIER_IDX_Pos)                        /**< (TC_QIER) Index Mask */
#define TC_QIER_IDX(value)                    (TC_QIER_IDX_Msk & ((value) << TC_QIER_IDX_Pos))    
#define TC_QIER_DIRCHG_Pos                    _U_(1)                                               /**< (TC_QIER) Direction Change Position */
#define TC_QIER_DIRCHG_Msk                    (_U_(0x1) << TC_QIER_DIRCHG_Pos)                     /**< (TC_QIER) Direction Change Mask */
#define TC_QIER_DIRCHG(value)                 (TC_QIER_DIRCHG_Msk & ((value) << TC_QIER_DIRCHG_Pos))
#define TC_QIER_QERR_Pos                      _U_(2)                                               /**< (TC_QIER) Quadrature Error Position */
#define TC_QIER_QERR_Msk                      (_U_(0x1) << TC_QIER_QERR_Pos)                       /**< (TC_QIER) Quadrature Error Mask */
#define TC_QIER_QERR(value)                   (TC_QIER_QERR_Msk & ((value) << TC_QIER_QERR_Pos))  
#define TC_QIER_FPHA_Pos                      _U_(4)                                               /**< (TC_QIER) Filtered Phase A Line Position */
#define TC_QIER_FPHA_Msk                      (_U_(0x1) << TC_QIER_FPHA_Pos)                       /**< (TC_QIER) Filtered Phase A Line Mask */
#define TC_QIER_FPHA(value)                   (TC_QIER_FPHA_Msk & ((value) << TC_QIER_FPHA_Pos))  
#define TC_QIER_FPHB_Pos                      _U_(5)                                               /**< (TC_QIER) Filtered Phase B Line Position */
#define TC_QIER_FPHB_Msk                      (_U_(0x1) << TC_QIER_FPHB_Pos)                       /**< (TC_QIER) Filtered Phase B Line Mask */
#define TC_QIER_FPHB(value)                   (TC_QIER_FPHB_Msk & ((value) << TC_QIER_FPHB_Pos))  
#define TC_QIER_FIDX_Pos                      _U_(6)                                               /**< (TC_QIER) Filtered Index Line Position */
#define TC_QIER_FIDX_Msk                      (_U_(0x1) << TC_QIER_FIDX_Pos)                       /**< (TC_QIER) Filtered Index Line Mask */
#define TC_QIER_FIDX(value)                   (TC_QIER_FIDX_Msk & ((value) << TC_QIER_FIDX_Pos))  
#define TC_QIER_FMP_Pos                       _U_(7)                                               /**< (TC_QIER) Filtered Missing Pulse Position */
#define TC_QIER_FMP_Msk                       (_U_(0x1) << TC_QIER_FMP_Pos)                        /**< (TC_QIER) Filtered Missing Pulse Mask */
#define TC_QIER_FMP(value)                    (TC_QIER_FMP_Msk & ((value) << TC_QIER_FMP_Pos))    
#define TC_QIER_Msk                           _U_(0x000000F7)                                      /**< (TC_QIER) Register Mask  */


/* -------- TC_QIDR : (TC Offset: 0xCC) ( /W 32) QDEC Interrupt Disable Register -------- */
#define TC_QIDR_IDX_Pos                       _U_(0)                                               /**< (TC_QIDR) Index Position */
#define TC_QIDR_IDX_Msk                       (_U_(0x1) << TC_QIDR_IDX_Pos)                        /**< (TC_QIDR) Index Mask */
#define TC_QIDR_IDX(value)                    (TC_QIDR_IDX_Msk & ((value) << TC_QIDR_IDX_Pos))    
#define TC_QIDR_DIRCHG_Pos                    _U_(1)                                               /**< (TC_QIDR) Direction Change Position */
#define TC_QIDR_DIRCHG_Msk                    (_U_(0x1) << TC_QIDR_DIRCHG_Pos)                     /**< (TC_QIDR) Direction Change Mask */
#define TC_QIDR_DIRCHG(value)                 (TC_QIDR_DIRCHG_Msk & ((value) << TC_QIDR_DIRCHG_Pos))
#define TC_QIDR_QERR_Pos                      _U_(2)                                               /**< (TC_QIDR) Quadrature Error Position */
#define TC_QIDR_QERR_Msk                      (_U_(0x1) << TC_QIDR_QERR_Pos)                       /**< (TC_QIDR) Quadrature Error Mask */
#define TC_QIDR_QERR(value)                   (TC_QIDR_QERR_Msk & ((value) << TC_QIDR_QERR_Pos))  
#define TC_QIDR_FPHA_Pos                      _U_(4)                                               /**< (TC_QIDR) Filtered Phase A Line Position */
#define TC_QIDR_FPHA_Msk                      (_U_(0x1) << TC_QIDR_FPHA_Pos)                       /**< (TC_QIDR) Filtered Phase A Line Mask */
#define TC_QIDR_FPHA(value)                   (TC_QIDR_FPHA_Msk & ((value) << TC_QIDR_FPHA_Pos))  
#define TC_QIDR_FPHB_Pos                      _U_(5)                                               /**< (TC_QIDR) Filtered Phase B Line Position */
#define TC_QIDR_FPHB_Msk                      (_U_(0x1) << TC_QIDR_FPHB_Pos)                       /**< (TC_QIDR) Filtered Phase B Line Mask */
#define TC_QIDR_FPHB(value)                   (TC_QIDR_FPHB_Msk & ((value) << TC_QIDR_FPHB_Pos))  
#define TC_QIDR_FIDX_Pos                      _U_(6)                                               /**< (TC_QIDR) Filtered Index Line Position */
#define TC_QIDR_FIDX_Msk                      (_U_(0x1) << TC_QIDR_FIDX_Pos)                       /**< (TC_QIDR) Filtered Index Line Mask */
#define TC_QIDR_FIDX(value)                   (TC_QIDR_FIDX_Msk & ((value) << TC_QIDR_FIDX_Pos))  
#define TC_QIDR_FMP_Pos                       _U_(7)                                               /**< (TC_QIDR) Filtered Missing Pulse Position */
#define TC_QIDR_FMP_Msk                       (_U_(0x1) << TC_QIDR_FMP_Pos)                        /**< (TC_QIDR) Filtered Missing Pulse Mask */
#define TC_QIDR_FMP(value)                    (TC_QIDR_FMP_Msk & ((value) << TC_QIDR_FMP_Pos))    
#define TC_QIDR_Msk                           _U_(0x000000F7)                                      /**< (TC_QIDR) Register Mask  */


/* -------- TC_QIMR : (TC Offset: 0xD0) ( R/ 32) QDEC Interrupt Mask Register -------- */
#define TC_QIMR_IDX_Pos                       _U_(0)                                               /**< (TC_QIMR) Index Position */
#define TC_QIMR_IDX_Msk                       (_U_(0x1) << TC_QIMR_IDX_Pos)                        /**< (TC_QIMR) Index Mask */
#define TC_QIMR_IDX(value)                    (TC_QIMR_IDX_Msk & ((value) << TC_QIMR_IDX_Pos))    
#define TC_QIMR_DIRCHG_Pos                    _U_(1)                                               /**< (TC_QIMR) Direction Change Position */
#define TC_QIMR_DIRCHG_Msk                    (_U_(0x1) << TC_QIMR_DIRCHG_Pos)                     /**< (TC_QIMR) Direction Change Mask */
#define TC_QIMR_DIRCHG(value)                 (TC_QIMR_DIRCHG_Msk & ((value) << TC_QIMR_DIRCHG_Pos))
#define TC_QIMR_QERR_Pos                      _U_(2)                                               /**< (TC_QIMR) Quadrature Error Position */
#define TC_QIMR_QERR_Msk                      (_U_(0x1) << TC_QIMR_QERR_Pos)                       /**< (TC_QIMR) Quadrature Error Mask */
#define TC_QIMR_QERR(value)                   (TC_QIMR_QERR_Msk & ((value) << TC_QIMR_QERR_Pos))  
#define TC_QIMR_FPHA_Pos                      _U_(4)                                               /**< (TC_QIMR) Filtered Phase A Line Position */
#define TC_QIMR_FPHA_Msk                      (_U_(0x1) << TC_QIMR_FPHA_Pos)                       /**< (TC_QIMR) Filtered Phase A Line Mask */
#define TC_QIMR_FPHA(value)                   (TC_QIMR_FPHA_Msk & ((value) << TC_QIMR_FPHA_Pos))  
#define TC_QIMR_FPHB_Pos                      _U_(5)                                               /**< (TC_QIMR) Filtered Phase B Line Position */
#define TC_QIMR_FPHB_Msk                      (_U_(0x1) << TC_QIMR_FPHB_Pos)                       /**< (TC_QIMR) Filtered Phase B Line Mask */
#define TC_QIMR_FPHB(value)                   (TC_QIMR_FPHB_Msk & ((value) << TC_QIMR_FPHB_Pos))  
#define TC_QIMR_FIDX_Pos                      _U_(6)                                               /**< (TC_QIMR) Filtered Index Line Position */
#define TC_QIMR_FIDX_Msk                      (_U_(0x1) << TC_QIMR_FIDX_Pos)                       /**< (TC_QIMR) Filtered Index Line Mask */
#define TC_QIMR_FIDX(value)                   (TC_QIMR_FIDX_Msk & ((value) << TC_QIMR_FIDX_Pos))  
#define TC_QIMR_FMP_Pos                       _U_(7)                                               /**< (TC_QIMR) Filtered Missing Pulse Position */
#define TC_QIMR_FMP_Msk                       (_U_(0x1) << TC_QIMR_FMP_Pos)                        /**< (TC_QIMR) Filtered Missing Pulse Mask */
#define TC_QIMR_FMP(value)                    (TC_QIMR_FMP_Msk & ((value) << TC_QIMR_FMP_Pos))    
#define TC_QIMR_Msk                           _U_(0x000000F7)                                      /**< (TC_QIMR) Register Mask  */


/* -------- TC_QISR : (TC Offset: 0xD4) ( R/ 32) QDEC Interrupt Status Register -------- */
#define TC_QISR_IDX_Pos                       _U_(0)                                               /**< (TC_QISR) Index Position */
#define TC_QISR_IDX_Msk                       (_U_(0x1) << TC_QISR_IDX_Pos)                        /**< (TC_QISR) Index Mask */
#define TC_QISR_IDX(value)                    (TC_QISR_IDX_Msk & ((value) << TC_QISR_IDX_Pos))    
#define TC_QISR_DIRCHG_Pos                    _U_(1)                                               /**< (TC_QISR) Direction Change Position */
#define TC_QISR_DIRCHG_Msk                    (_U_(0x1) << TC_QISR_DIRCHG_Pos)                     /**< (TC_QISR) Direction Change Mask */
#define TC_QISR_DIRCHG(value)                 (TC_QISR_DIRCHG_Msk & ((value) << TC_QISR_DIRCHG_Pos))
#define TC_QISR_QERR_Pos                      _U_(2)                                               /**< (TC_QISR) Quadrature Error Position */
#define TC_QISR_QERR_Msk                      (_U_(0x1) << TC_QISR_QERR_Pos)                       /**< (TC_QISR) Quadrature Error Mask */
#define TC_QISR_QERR(value)                   (TC_QISR_QERR_Msk & ((value) << TC_QISR_QERR_Pos))  
#define TC_QISR_FPHA_Pos                      _U_(4)                                               /**< (TC_QISR) Filtered Phase A Line Position */
#define TC_QISR_FPHA_Msk                      (_U_(0x1) << TC_QISR_FPHA_Pos)                       /**< (TC_QISR) Filtered Phase A Line Mask */
#define TC_QISR_FPHA(value)                   (TC_QISR_FPHA_Msk & ((value) << TC_QISR_FPHA_Pos))  
#define TC_QISR_FPHB_Pos                      _U_(5)                                               /**< (TC_QISR) Filtered Phase B Line Position */
#define TC_QISR_FPHB_Msk                      (_U_(0x1) << TC_QISR_FPHB_Pos)                       /**< (TC_QISR) Filtered Phase B Line Mask */
#define TC_QISR_FPHB(value)                   (TC_QISR_FPHB_Msk & ((value) << TC_QISR_FPHB_Pos))  
#define TC_QISR_FIDX_Pos                      _U_(6)                                               /**< (TC_QISR) Filtered Index Line Position */
#define TC_QISR_FIDX_Msk                      (_U_(0x1) << TC_QISR_FIDX_Pos)                       /**< (TC_QISR) Filtered Index Line Mask */
#define TC_QISR_FIDX(value)                   (TC_QISR_FIDX_Msk & ((value) << TC_QISR_FIDX_Pos))  
#define TC_QISR_FMP_Pos                       _U_(7)                                               /**< (TC_QISR) Filtered Missing Pulse Position */
#define TC_QISR_FMP_Msk                       (_U_(0x1) << TC_QISR_FMP_Pos)                        /**< (TC_QISR) Filtered Missing Pulse Mask */
#define TC_QISR_FMP(value)                    (TC_QISR_FMP_Msk & ((value) << TC_QISR_FMP_Pos))    
#define TC_QISR_DIR_Pos                       _U_(8)                                               /**< (TC_QISR) Direction Position */
#define TC_QISR_DIR_Msk                       (_U_(0x1) << TC_QISR_DIR_Pos)                        /**< (TC_QISR) Direction Mask */
#define TC_QISR_DIR(value)                    (TC_QISR_DIR_Msk & ((value) << TC_QISR_DIR_Pos))    
#define TC_QISR_Msk                           _U_(0x000001F7)                                      /**< (TC_QISR) Register Mask  */


/* -------- TC_FMR : (TC Offset: 0xD8) (R/W 32) Fault Mode Register -------- */
#define TC_FMR_ENCF0_Pos                      _U_(0)                                               /**< (TC_FMR) Enable Compare Fault Channel 0 Position */
#define TC_FMR_ENCF0_Msk                      (_U_(0x1) << TC_FMR_ENCF0_Pos)                       /**< (TC_FMR) Enable Compare Fault Channel 0 Mask */
#define TC_FMR_ENCF0(value)                   (TC_FMR_ENCF0_Msk & ((value) << TC_FMR_ENCF0_Pos))  
#define TC_FMR_ENCF1_Pos                      _U_(1)                                               /**< (TC_FMR) Enable Compare Fault Channel 1 Position */
#define TC_FMR_ENCF1_Msk                      (_U_(0x1) << TC_FMR_ENCF1_Pos)                       /**< (TC_FMR) Enable Compare Fault Channel 1 Mask */
#define TC_FMR_ENCF1(value)                   (TC_FMR_ENCF1_Msk & ((value) << TC_FMR_ENCF1_Pos))  
#define TC_FMR_Msk                            _U_(0x00000003)                                      /**< (TC_FMR) Register Mask  */

#define TC_FMR_ENCF_Pos                       _U_(0)                                               /**< (TC_FMR Position) Enable Compare Fault Channel x */
#define TC_FMR_ENCF_Msk                       (_U_(0x3) << TC_FMR_ENCF_Pos)                        /**< (TC_FMR Mask) ENCF */
#define TC_FMR_ENCF(value)                    (TC_FMR_ENCF_Msk & ((value) << TC_FMR_ENCF_Pos))     

/* -------- TC_QSR : (TC Offset: 0xDC) ( R/ 32) QDEC Status Register -------- */
#define TC_QSR_DIR_Pos                        _U_(8)                                               /**< (TC_QSR) Direction Position */
#define TC_QSR_DIR_Msk                        (_U_(0x1) << TC_QSR_DIR_Pos)                         /**< (TC_QSR) Direction Mask */
#define TC_QSR_DIR(value)                     (TC_QSR_DIR_Msk & ((value) << TC_QSR_DIR_Pos))      
#define TC_QSR_Msk                            _U_(0x00000100)                                      /**< (TC_QSR) Register Mask  */


/* -------- TC_WPMR : (TC Offset: 0xE4) (R/W 32) Write Protection Mode Register -------- */
#define TC_WPMR_WPEN_Pos                      _U_(0)                                               /**< (TC_WPMR) Write Protection Enable Position */
#define TC_WPMR_WPEN_Msk                      (_U_(0x1) << TC_WPMR_WPEN_Pos)                       /**< (TC_WPMR) Write Protection Enable Mask */
#define TC_WPMR_WPEN(value)                   (TC_WPMR_WPEN_Msk & ((value) << TC_WPMR_WPEN_Pos))  
#define TC_WPMR_WPITEN_Pos                    _U_(1)                                               /**< (TC_WPMR) Write Protection Interrupt Enable Position */
#define TC_WPMR_WPITEN_Msk                    (_U_(0x1) << TC_WPMR_WPITEN_Pos)                     /**< (TC_WPMR) Write Protection Interrupt Enable Mask */
#define TC_WPMR_WPITEN(value)                 (TC_WPMR_WPITEN_Msk & ((value) << TC_WPMR_WPITEN_Pos))
#define TC_WPMR_WPCREN_Pos                    _U_(2)                                               /**< (TC_WPMR) Write Protection Control Enable Position */
#define TC_WPMR_WPCREN_Msk                    (_U_(0x1) << TC_WPMR_WPCREN_Pos)                     /**< (TC_WPMR) Write Protection Control Enable Mask */
#define TC_WPMR_WPCREN(value)                 (TC_WPMR_WPCREN_Msk & ((value) << TC_WPMR_WPCREN_Pos))
#define TC_WPMR_FIRSTE_Pos                    _U_(4)                                               /**< (TC_WPMR) First Error Report Enable Position */
#define TC_WPMR_FIRSTE_Msk                    (_U_(0x1) << TC_WPMR_FIRSTE_Pos)                     /**< (TC_WPMR) First Error Report Enable Mask */
#define TC_WPMR_FIRSTE(value)                 (TC_WPMR_FIRSTE_Msk & ((value) << TC_WPMR_FIRSTE_Pos))
#define TC_WPMR_WPKEY_Pos                     _U_(8)                                               /**< (TC_WPMR) Write Protection Key Position */
#define TC_WPMR_WPKEY_Msk                     (_U_(0xFFFFFF) << TC_WPMR_WPKEY_Pos)                 /**< (TC_WPMR) Write Protection Key Mask */
#define TC_WPMR_WPKEY(value)                  (TC_WPMR_WPKEY_Msk & ((value) << TC_WPMR_WPKEY_Pos))
#define   TC_WPMR_WPKEY_PASSWD_Val            _U_(0x54494D)                                        /**< (TC_WPMR) Writing any other value in this field aborts the write operation of the WPEN bit.Always reads as 0.  */
#define TC_WPMR_WPKEY_PASSWD                  (TC_WPMR_WPKEY_PASSWD_Val << TC_WPMR_WPKEY_Pos)      /**< (TC_WPMR) Writing any other value in this field aborts the write operation of the WPEN bit.Always reads as 0. Position  */
#define TC_WPMR_Msk                           _U_(0xFFFFFF17)                                      /**< (TC_WPMR) Register Mask  */


/* -------- TC_VER : (TC Offset: 0xFC) ( R/ 32) Version Register -------- */
#define TC_VER_VERSION_Pos                    _U_(0)                                               /**< (TC_VER) Version of the Hardware Module Position */
#define TC_VER_VERSION_Msk                    (_U_(0xFFF) << TC_VER_VERSION_Pos)                   /**< (TC_VER) Version of the Hardware Module Mask */
#define TC_VER_VERSION(value)                 (TC_VER_VERSION_Msk & ((value) << TC_VER_VERSION_Pos))
#define TC_VER_MFN_Pos                        _U_(16)                                              /**< (TC_VER) Metal Fix Number Position */
#define TC_VER_MFN_Msk                        (_U_(0x7) << TC_VER_MFN_Pos)                         /**< (TC_VER) Metal Fix Number Mask */
#define TC_VER_MFN(value)                     (TC_VER_MFN_Msk & ((value) << TC_VER_MFN_Pos))      
#define TC_VER_Msk                            _U_(0x00070FFF)                                      /**< (TC_VER) Register Mask  */


/** \brief TC register offsets definitions */
#define TC_CCR_REG_OFST                (0x00)              /**< (TC_CCR) Channel Control Register Offset */
#define TC_CMR_REG_OFST                (0x04)              /**< (TC_CMR) Channel Mode Register Offset */
#define TC_SMMR_REG_OFST               (0x08)              /**< (TC_SMMR) Stepper Motor Mode Register Offset */
#define TC_RAB_REG_OFST                (0x0C)              /**< (TC_RAB) Register AB Offset */
#define TC_CV_REG_OFST                 (0x10)              /**< (TC_CV) Counter Value Offset */
#define TC_RA_REG_OFST                 (0x14)              /**< (TC_RA) Register A Offset */
#define TC_RB_REG_OFST                 (0x18)              /**< (TC_RB) Register B Offset */
#define TC_RC_REG_OFST                 (0x1C)              /**< (TC_RC) Register C Offset */
#define TC_SR_REG_OFST                 (0x20)              /**< (TC_SR) Interrupt Status Register Offset */
#define TC_IER_REG_OFST                (0x24)              /**< (TC_IER) Interrupt Enable Register Offset */
#define TC_IDR_REG_OFST                (0x28)              /**< (TC_IDR) Interrupt Disable Register Offset */
#define TC_IMR_REG_OFST                (0x2C)              /**< (TC_IMR) Interrupt Mask Register Offset */
#define TC_EMR_REG_OFST                (0x30)              /**< (TC_EMR) Extended Mode Register Offset */
#define TC_CSR_REG_OFST                (0x34)              /**< (TC_CSR) Channel Status Register Offset */
#define TC_SSR_REG_OFST                (0x38)              /**< (TC_SSR) Safety Status Register Offset */
#define TC_BCR_REG_OFST                (0xC0)              /**< (TC_BCR) Block Control Register Offset */
#define TC_BMR_REG_OFST                (0xC4)              /**< (TC_BMR) Block Mode Register Offset */
#define TC_QIER_REG_OFST               (0xC8)              /**< (TC_QIER) QDEC Interrupt Enable Register Offset */
#define TC_QIDR_REG_OFST               (0xCC)              /**< (TC_QIDR) QDEC Interrupt Disable Register Offset */
#define TC_QIMR_REG_OFST               (0xD0)              /**< (TC_QIMR) QDEC Interrupt Mask Register Offset */
#define TC_QISR_REG_OFST               (0xD4)              /**< (TC_QISR) QDEC Interrupt Status Register Offset */
#define TC_FMR_REG_OFST                (0xD8)              /**< (TC_FMR) Fault Mode Register Offset */
#define TC_QSR_REG_OFST                (0xDC)              /**< (TC_QSR) QDEC Status Register Offset */
#define TC_WPMR_REG_OFST               (0xE4)              /**< (TC_WPMR) Write Protection Mode Register Offset */
#define TC_VER_REG_OFST                (0xFC)              /**< (TC_VER) Version Register Offset */

#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief TC_CHANNEL register API structure */
typedef struct
{
  __O   uint32_t                       TC_CCR;             /**< Offset: 0x00 ( /W  32) Channel Control Register */
  __IO  uint32_t                       TC_CMR;             /**< Offset: 0x04 (R/W  32) Channel Mode Register */
  __IO  uint32_t                       TC_SMMR;            /**< Offset: 0x08 (R/W  32) Stepper Motor Mode Register */
  __I   uint32_t                       TC_RAB;             /**< Offset: 0x0C (R/   32) Register AB */
  __I   uint32_t                       TC_CV;              /**< Offset: 0x10 (R/   32) Counter Value */
  __IO  uint32_t                       TC_RA;              /**< Offset: 0x14 (R/W  32) Register A */
  __IO  uint32_t                       TC_RB;              /**< Offset: 0x18 (R/W  32) Register B */
  __IO  uint32_t                       TC_RC;              /**< Offset: 0x1C (R/W  32) Register C */
  __I   uint32_t                       TC_SR;              /**< Offset: 0x20 (R/   32) Interrupt Status Register */
  __O   uint32_t                       TC_IER;             /**< Offset: 0x24 ( /W  32) Interrupt Enable Register */
  __O   uint32_t                       TC_IDR;             /**< Offset: 0x28 ( /W  32) Interrupt Disable Register */
  __I   uint32_t                       TC_IMR;             /**< Offset: 0x2C (R/   32) Interrupt Mask Register */
  __IO  uint32_t                       TC_EMR;             /**< Offset: 0x30 (R/W  32) Extended Mode Register */
  __I   uint32_t                       TC_CSR;             /**< Offset: 0x34 (R/   32) Channel Status Register */
  __I   uint32_t                       TC_SSR;             /**< Offset: 0x38 (R/   32) Safety Status Register */
  __I   uint8_t                        Reserved1[0x04];
} tc_channel_registers_t;

#define TC_CHANNEL_NUMBER _U_(3)

/** \brief TC register API structure */
typedef struct
{
        tc_channel_registers_t         TC_CHANNEL[TC_CHANNEL_NUMBER]; /**< Offset: 0x00  */
  __O   uint32_t                       TC_BCR;             /**< Offset: 0xC0 ( /W  32) Block Control Register */
  __IO  uint32_t                       TC_BMR;             /**< Offset: 0xC4 (R/W  32) Block Mode Register */
  __O   uint32_t                       TC_QIER;            /**< Offset: 0xC8 ( /W  32) QDEC Interrupt Enable Register */
  __O   uint32_t                       TC_QIDR;            /**< Offset: 0xCC ( /W  32) QDEC Interrupt Disable Register */
  __I   uint32_t                       TC_QIMR;            /**< Offset: 0xD0 (R/   32) QDEC Interrupt Mask Register */
  __I   uint32_t                       TC_QISR;            /**< Offset: 0xD4 (R/   32) QDEC Interrupt Status Register */
  __IO  uint32_t                       TC_FMR;             /**< Offset: 0xD8 (R/W  32) Fault Mode Register */
  __I   uint32_t                       TC_QSR;             /**< Offset: 0xDC (R/   32) QDEC Status Register */
  __I   uint8_t                        Reserved1[0x04];
  __IO  uint32_t                       TC_WPMR;            /**< Offset: 0xE4 (R/W  32) Write Protection Mode Register */
  __I   uint8_t                        Reserved2[0x14];
  __I   uint32_t                       TC_VER;             /**< Offset: 0xFC (R/   32) Version Register */
} tc_registers_t;


#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */
#endif /* _SAM9X_TC_COMPONENT_H_ */
