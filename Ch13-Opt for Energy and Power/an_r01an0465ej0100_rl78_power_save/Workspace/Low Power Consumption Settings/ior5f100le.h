/*-------------------------------------------------------------------------
 *      Declarations of SFR registers, interrupt and callt vector addresses
 *      for RL78 microcontroller R5F100LE.
 *
 *      This file can be used by both the RL78,
 *      Assembler, ARL78, and the C/C++ compiler, ICCRL78.
 *
 *      This header file is generated from the device file:
 *          DR5F100LE.DVF
 *          Copyright(C) 2011 Renesas
 *          Format version V3.00, File version E1.00d
 *-------------------------------------------------------------------------*/

#ifndef __IOR5F100LE_H__
#define __IOR5F100LE_H__

#if !defined(__ARL78__) && !defined(__ICCRL78__)
  #error "IOR5F100LE.H file for use with RL78 Assembler or Compiler only"
#endif

#if defined(__ARL78__)
  #if __CORE__ != __RL78_1__
    #error "IOR5F100LE.H file for use with ARL78 option --core rl78_1 only"
  #endif
#endif
#if defined(__ICCRL78__)
  #if __CORE__ != __RL78_1__
    #error "IOR5F100LE.H file for use with ICCRL78 option --core rl78_1 only"
  #endif
#endif

#ifdef __IAR_SYSTEMS_ICC__

#pragma language=extended
#pragma system_include

/*----------------------------------------------
 * SFR bits (default names)
 *--------------------------------------------*/

#ifndef __RL78_BIT_STRUCTURE__
  #define __RL78_BIT_STRUCTURE__
  typedef struct
  {
    unsigned char no0:1;
    unsigned char no1:1;
    unsigned char no2:1;
    unsigned char no3:1;
    unsigned char no4:1;
    unsigned char no5:1;
    unsigned char no6:1;
    unsigned char no7:1;
  } __BITS8;
#endif

/*----------------------------------------------
 *       SFR declarations
 *--------------------------------------------*/

__saddr __no_init volatile union { unsigned char P0; __BITS8 P0_bit; } @ 0xFFF00;
__saddr __no_init volatile union { unsigned char P1; __BITS8 P1_bit; } @ 0xFFF01;
__saddr __no_init volatile union { unsigned char P2; __BITS8 P2_bit; } @ 0xFFF02;
__saddr __no_init volatile union { unsigned char P3; __BITS8 P3_bit; } @ 0xFFF03;
__saddr __no_init volatile union { unsigned char P4; __BITS8 P4_bit; } @ 0xFFF04;
__saddr __no_init volatile union { unsigned char P5; __BITS8 P5_bit; } @ 0xFFF05;
__saddr __no_init volatile union { unsigned char P6; __BITS8 P6_bit; } @ 0xFFF06;
__saddr __no_init volatile union { unsigned char P7; __BITS8 P7_bit; } @ 0xFFF07;
__saddr __no_init volatile union { unsigned char P12; __BITS8 P12_bit; } @ 0xFFF0C;
__saddr __no_init volatile union { unsigned char P13; __BITS8 P13_bit; } @ 0xFFF0D;
__saddr __no_init volatile union { unsigned char P14; __BITS8 P14_bit; } @ 0xFFF0E;
__saddr __no_init volatile union { unsigned short SDR00; struct { unsigned char TXD0; unsigned char SIO00; }; } @ 0xFFF10;
__saddr __no_init volatile union { unsigned short SDR01; struct { unsigned char RXD0; unsigned char SIO01; }; } @ 0xFFF12;
__saddr __no_bit_access __no_init volatile unsigned short TDR00 @ 0xFFF18;
__saddr __no_bit_access __no_init volatile union { unsigned short TDR01; struct { unsigned char TDR01L; unsigned char TDR01H; }; } @ 0xFFF1A;
__saddr __no_bit_access __no_init volatile const union { unsigned short ADCR; struct { unsigned char :8; const unsigned char ADCRH; }; } @ 0xFFF1E;
__sfr __no_init volatile union { unsigned char PM0; __BITS8 PM0_bit; } @ 0xFFF20;
__sfr __no_init volatile union { unsigned char PM1; __BITS8 PM1_bit; } @ 0xFFF21;
__sfr __no_init volatile union { unsigned char PM2; __BITS8 PM2_bit; } @ 0xFFF22;
__sfr __no_init volatile union { unsigned char PM3; __BITS8 PM3_bit; } @ 0xFFF23;
__sfr __no_init volatile union { unsigned char PM4; __BITS8 PM4_bit; } @ 0xFFF24;
__sfr __no_init volatile union { unsigned char PM5; __BITS8 PM5_bit; } @ 0xFFF25;
__sfr __no_init volatile union { unsigned char PM6; __BITS8 PM6_bit; } @ 0xFFF26;
__sfr __no_init volatile union { unsigned char PM7; __BITS8 PM7_bit; } @ 0xFFF27;
__sfr __no_init volatile union { unsigned char PM12; __BITS8 PM12_bit; } @ 0xFFF2C;
__sfr __no_init volatile union { unsigned char PM14; __BITS8 PM14_bit; } @ 0xFFF2E;
__sfr __no_init volatile union { unsigned char ADM0; __BITS8 ADM0_bit; } @ 0xFFF30;
__sfr __no_init volatile union { unsigned char ADS; __BITS8 ADS_bit; } @ 0xFFF31;
__sfr __no_init volatile union { unsigned char ADM1; __BITS8 ADM1_bit; } @ 0xFFF32;
__sfr __no_init volatile union { unsigned char KRM; __BITS8 KRM_bit; } @ 0xFFF37;
__sfr __no_init volatile union { unsigned char EGP0; __BITS8 EGP0_bit; } @ 0xFFF38;
__sfr __no_init volatile union { unsigned char EGN0; __BITS8 EGN0_bit; } @ 0xFFF39;
__sfr __no_init volatile union { unsigned char EGP1; __BITS8 EGP1_bit; } @ 0xFFF3A;
__sfr __no_init volatile union { unsigned char EGN1; __BITS8 EGN1_bit; } @ 0xFFF3B;
__sfr __no_init volatile union { unsigned short SDR02; struct { unsigned char SIO10; unsigned char TXD1; }; } @ 0xFFF44;
__sfr __no_init volatile union { unsigned short SDR03; struct { unsigned char RXD1; unsigned char SIO11; }; } @ 0xFFF46;
__sfr __no_init volatile union { unsigned short SDR10; struct { unsigned char SIO20; unsigned char TXD2; }; } @ 0xFFF48;
__sfr __no_init volatile union { unsigned short SDR11; struct { unsigned char RXD2; unsigned char SIO21; }; } @ 0xFFF4A;
__sfr __no_bit_access __no_init volatile unsigned char IICA0 @ 0xFFF50;
__sfr __no_init volatile const union { unsigned char IICS0; __BITS8 IICS0_bit; } @ 0xFFF51;
__sfr __no_init volatile union { unsigned char IICF0; __BITS8 IICF0_bit; } @ 0xFFF52;
__sfr __no_bit_access __no_init volatile unsigned short TDR02 @ 0xFFF64;
__sfr __no_bit_access __no_init volatile union { unsigned short TDR03; struct { unsigned char TDR03L; unsigned char TDR03H; }; } @ 0xFFF66;
__sfr __no_bit_access __no_init volatile unsigned short TDR04 @ 0xFFF68;
__sfr __no_bit_access __no_init volatile unsigned short TDR05 @ 0xFFF6A;
__sfr __no_bit_access __no_init volatile unsigned short TDR06 @ 0xFFF6C;
__sfr __no_bit_access __no_init volatile unsigned short TDR07 @ 0xFFF6E;
__sfr __no_bit_access __no_init volatile unsigned short ITMC @ 0xFFF90;
__sfr __no_bit_access __no_init volatile unsigned char SEC @ 0xFFF92;
__sfr __no_bit_access __no_init volatile unsigned char MIN @ 0xFFF93;
__sfr __no_bit_access __no_init volatile unsigned char HOUR @ 0xFFF94;
__sfr __no_bit_access __no_init volatile unsigned char WEEK @ 0xFFF95;
__sfr __no_bit_access __no_init volatile unsigned char DAY @ 0xFFF96;
__sfr __no_bit_access __no_init volatile unsigned char MONTH @ 0xFFF97;
__sfr __no_bit_access __no_init volatile unsigned char YEAR @ 0xFFF98;
__sfr __no_bit_access __no_init volatile unsigned char SUBCUD @ 0xFFF99;
__sfr __no_bit_access __no_init volatile unsigned char ALARMWM @ 0xFFF9A;
__sfr __no_bit_access __no_init volatile unsigned char ALARMWH @ 0xFFF9B;
__sfr __no_bit_access __no_init volatile unsigned char ALARMWW @ 0xFFF9C;
__sfr __no_init volatile union { unsigned char RTCC0; __BITS8 RTCC0_bit; } @ 0xFFF9D;
__sfr __no_init volatile union { unsigned char RTCC1; __BITS8 RTCC1_bit; } @ 0xFFF9E;
__sfr __no_bit_access __no_init volatile unsigned char CMC @ 0xFFFA0;
__sfr __no_init volatile union { unsigned char CSC; __BITS8 CSC_bit; } @ 0xFFFA1;
__sfr __no_init volatile const union { unsigned char OSTC; __BITS8 OSTC_bit; } @ 0xFFFA2;
__sfr __no_bit_access __no_init volatile unsigned char OSTS @ 0xFFFA3;
__sfr __no_init volatile union { unsigned char CKC; __BITS8 CKC_bit; } @ 0xFFFA4;
__sfr __no_init volatile union { unsigned char CKS0; __BITS8 CKS0_bit; } @ 0xFFFA5;
__sfr __no_init volatile union { unsigned char CKS1; __BITS8 CKS1_bit; } @ 0xFFFA6;
__sfr __no_bit_access __no_init volatile const unsigned char RESF @ 0xFFFA8;
__sfr __no_init volatile union { unsigned char LVIM; __BITS8 LVIM_bit; } @ 0xFFFA9;
__sfr __no_init volatile union { unsigned char LVIS; __BITS8 LVIS_bit; } @ 0xFFFAA;
__sfr __no_bit_access __no_init volatile unsigned char WDTE @ 0xFFFAB;
__sfr __no_bit_access __no_init volatile unsigned char CRCIN @ 0xFFFAC;
__sfr __no_bit_access __no_init volatile unsigned char DSA0 @ 0xFFFB0;
__sfr __no_bit_access __no_init volatile unsigned char DSA1 @ 0xFFFB1;
__sfr __no_bit_access __no_init volatile union { unsigned short DRA0; struct { unsigned char DRA0L; unsigned char DRA0H; }; } @ 0xFFFB2;
__sfr __no_bit_access __no_init volatile union { unsigned short DRA1; struct { unsigned char DRA1L; unsigned char DRA1H; }; } @ 0xFFFB4;
__sfr __no_bit_access __no_init volatile union { unsigned short DBC0; struct { unsigned char DBC0L; unsigned char DBC0H; }; } @ 0xFFFB6;
__sfr __no_bit_access __no_init volatile union { unsigned short DBC1; struct { unsigned char DBC1L; unsigned char DBC1H; }; } @ 0xFFFB8;
__sfr __no_init volatile union { unsigned char DMC0; __BITS8 DMC0_bit; } @ 0xFFFBA;
__sfr __no_init volatile union { unsigned char DMC1; __BITS8 DMC1_bit; } @ 0xFFFBB;
__sfr __no_init volatile union { unsigned char DRC0; __BITS8 DRC0_bit; } @ 0xFFFBC;
__sfr __no_init volatile union { unsigned char DRC1; __BITS8 DRC1_bit; } @ 0xFFFBD;
__sfr __no_init volatile union { unsigned short IF2; struct { union { unsigned char IF2L; __BITS8 IF2L_bit; }; union { unsigned char IF2H; __BITS8 IF2H_bit; }; }; } @ 0xFFFD0;
__sfr __no_init volatile union { unsigned short MK2; struct { union { unsigned char MK2L; __BITS8 MK2L_bit; }; union { unsigned char MK2H; __BITS8 MK2H_bit; }; }; } @ 0xFFFD4;
__sfr __no_init volatile union { unsigned short PR02; struct { union { unsigned char PR02L; __BITS8 PR02L_bit; }; union { unsigned char PR02H; __BITS8 PR02H_bit; }; }; } @ 0xFFFD8;
__sfr __no_init volatile union { unsigned short PR12; struct { union { unsigned char PR12L; __BITS8 PR12L_bit; }; union { unsigned char PR12H; __BITS8 PR12H_bit; }; }; } @ 0xFFFDC;
__sfr __no_init volatile union { unsigned short IF0; struct { union { unsigned char IF0L; __BITS8 IF0L_bit; }; union { unsigned char IF0H; __BITS8 IF0H_bit; }; }; } @ 0xFFFE0;
__sfr __no_init volatile union { unsigned short IF1; struct { union { unsigned char IF1L; __BITS8 IF1L_bit; }; union { unsigned char IF1H; __BITS8 IF1H_bit; }; }; } @ 0xFFFE2;
__sfr __no_init volatile union { unsigned short MK0; struct { union { unsigned char MK0L; __BITS8 MK0L_bit; }; union { unsigned char MK0H; __BITS8 MK0H_bit; }; }; } @ 0xFFFE4;
__sfr __no_init volatile union { unsigned short MK1; struct { union { unsigned char MK1L; __BITS8 MK1L_bit; }; union { unsigned char MK1H; __BITS8 MK1H_bit; }; }; } @ 0xFFFE6;
__sfr __no_init volatile union { unsigned short PR00; struct { union { unsigned char PR00L; __BITS8 PR00L_bit; }; union { unsigned char PR00H; __BITS8 PR00H_bit; }; }; } @ 0xFFFE8;
__sfr __no_init volatile union { unsigned short PR01; struct { union { unsigned char PR01L; __BITS8 PR01L_bit; }; union { unsigned char PR01H; __BITS8 PR01H_bit; }; }; } @ 0xFFFEA;
__sfr __no_init volatile union { unsigned short PR10; struct { union { unsigned char PR10L; __BITS8 PR10L_bit; }; union { unsigned char PR10H; __BITS8 PR10H_bit; }; }; } @ 0xFFFEC;
__sfr __no_init volatile union { unsigned short PR11; struct { union { unsigned char PR11L; __BITS8 PR11L_bit; }; union { unsigned char PR11H; __BITS8 PR11H_bit; }; }; } @ 0xFFFEE;
__sfr __no_bit_access __no_init volatile unsigned short MDAL @ 0xFFFF0;
__sfr __no_bit_access __no_init volatile unsigned short MULA @ 0xFFFF0;
__sfr __no_bit_access __no_init volatile unsigned short MDAH @ 0xFFFF2;
__sfr __no_bit_access __no_init volatile unsigned short MULB @ 0xFFFF2;
__sfr __no_bit_access __no_init volatile unsigned short MDBH @ 0xFFFF4;
__sfr __no_bit_access __no_init volatile unsigned short MULOH @ 0xFFFF4;
__sfr __no_bit_access __no_init volatile unsigned short MDBL @ 0xFFFF6;
__sfr __no_bit_access __no_init volatile unsigned short MULOL @ 0xFFFF6;
__sfr __no_init volatile union { unsigned char PMC; __BITS8 PMC_bit; } @ 0xFFFFE;

/*----------------------------------------------
 *       SFR bit declarations
 *--------------------------------------------*/

#define ADCE              ADM0_bit.no0
#define ADCS              ADM0_bit.no7

#define SPD0              IICS0_bit.no0
#define STD0              IICS0_bit.no1
#define ACKD0             IICS0_bit.no2
#define TRC0              IICS0_bit.no3
#define COI0              IICS0_bit.no4
#define EXC0              IICS0_bit.no5
#define ALD0              IICS0_bit.no6
#define MSTS0             IICS0_bit.no7

#define IICRSV0           IICF0_bit.no0
#define STCEN0            IICF0_bit.no1
#define IICBSY0           IICF0_bit.no6
#define STCF0             IICF0_bit.no7

#define RCLOE1            RTCC0_bit.no5
#define RTCE              RTCC0_bit.no7

#define RWAIT             RTCC1_bit.no0
#define RWST              RTCC1_bit.no1
#define RIFG              RTCC1_bit.no3
#define WAFG              RTCC1_bit.no4
#define WALIE             RTCC1_bit.no6
#define WALE              RTCC1_bit.no7

#define HIOSTOP           CSC_bit.no0
#define XTSTOP            CSC_bit.no6
#define MSTOP             CSC_bit.no7

#define SDIV              CKC_bit.no3
#define MCM0              CKC_bit.no4
#define MCS               CKC_bit.no5
#define CSS               CKC_bit.no6
#define CLS               CKC_bit.no7

#define PCLOE0            CKS0_bit.no7

#define PCLOE1            CKS1_bit.no7

#define LVIF              LVIM_bit.no0
#define LVIOMSK           LVIM_bit.no1
#define LVISEN            LVIM_bit.no7

#define LVILV             LVIS_bit.no0
#define LVIMD             LVIS_bit.no7

#define DWAIT0            DMC0_bit.no4
#define DS0               DMC0_bit.no5
#define DRS0              DMC0_bit.no6
#define STG0              DMC0_bit.no7

#define DWAIT1            DMC1_bit.no4
#define DS1               DMC1_bit.no5
#define DRS1              DMC1_bit.no6
#define STG1              DMC1_bit.no7

#define DST0              DRC0_bit.no0
#define DEN0              DRC0_bit.no7

#define DST1              DRC1_bit.no0
#define DEN1              DRC1_bit.no7

#define TMIF05            IF2L_bit.no0
#define TMIF06            IF2L_bit.no1
#define TMIF07            IF2L_bit.no2
#define PIF6              IF2L_bit.no3
#define PIF7              IF2L_bit.no4
#define PIF8              IF2L_bit.no5
#define PIF9              IF2L_bit.no6
#define PIF10             IF2L_bit.no7

#define PIF11             IF2H_bit.no0
#define MDIF              IF2H_bit.no5
#define FLIF              IF2H_bit.no7

#define TMMK05            MK2L_bit.no0
#define TMMK06            MK2L_bit.no1
#define TMMK07            MK2L_bit.no2
#define PMK6              MK2L_bit.no3
#define PMK7              MK2L_bit.no4
#define PMK8              MK2L_bit.no5
#define PMK9              MK2L_bit.no6
#define PMK10             MK2L_bit.no7

#define PMK11             MK2H_bit.no0
#define MDMK              MK2H_bit.no5
#define FLMK              MK2H_bit.no7

#define TMPR005           PR02L_bit.no0
#define TMPR006           PR02L_bit.no1
#define TMPR007           PR02L_bit.no2
#define PPR06             PR02L_bit.no3
#define PPR07             PR02L_bit.no4
#define PPR08             PR02L_bit.no5
#define PPR09             PR02L_bit.no6
#define PPR010            PR02L_bit.no7

#define PPR011            PR02H_bit.no0
#define MDPR0             PR02H_bit.no5
#define FLPR0             PR02H_bit.no7

#define TMPR105           PR12L_bit.no0
#define TMPR106           PR12L_bit.no1
#define TMPR107           PR12L_bit.no2
#define PPR16             PR12L_bit.no3
#define PPR17             PR12L_bit.no4
#define PPR18             PR12L_bit.no5
#define PPR19             PR12L_bit.no6
#define PPR110            PR12L_bit.no7

#define PPR111            PR12H_bit.no0
#define MDPR1             PR12H_bit.no5
#define FLPR1             PR12H_bit.no7

#define WDTIIF            IF0L_bit.no0
#define LVIIF             IF0L_bit.no1
#define PIF0              IF0L_bit.no2
#define PIF1              IF0L_bit.no3
#define PIF2              IF0L_bit.no4
#define PIF3              IF0L_bit.no5
#define PIF4              IF0L_bit.no6
#define PIF5              IF0L_bit.no7

#define CSIIF20           IF0H_bit.no0
#define IICIF20           IF0H_bit.no0
#define STIF2             IF0H_bit.no0
#define CSIIF21           IF0H_bit.no1
#define IICIF21           IF0H_bit.no1
#define SRIF2             IF0H_bit.no1
#define SREIF2            IF0H_bit.no2
#define DMAIF0            IF0H_bit.no3
#define DMAIF1            IF0H_bit.no4
#define CSIIF00           IF0H_bit.no5
#define IICIF00           IF0H_bit.no5
#define STIF0             IF0H_bit.no5
#define CSIIF01           IF0H_bit.no6
#define IICIF01           IF0H_bit.no6
#define SRIF0             IF0H_bit.no6
#define SREIF0            IF0H_bit.no7
#define TMIF01H           IF0H_bit.no7

#define CSIIF10           IF1L_bit.no0
#define IICIF10           IF1L_bit.no0
#define STIF1             IF1L_bit.no0
#define CSIIF11           IF1L_bit.no1
#define IICIF11           IF1L_bit.no1
#define SRIF1             IF1L_bit.no1
#define SREIF1            IF1L_bit.no2
#define TMIF03H           IF1L_bit.no2
#define IICAIF0           IF1L_bit.no3
#define TMIF00            IF1L_bit.no4
#define TMIF01            IF1L_bit.no5
#define TMIF02            IF1L_bit.no6
#define TMIF03            IF1L_bit.no7

#define ADIF              IF1H_bit.no0
#define RTCIF             IF1H_bit.no1
#define ITIF              IF1H_bit.no2
#define KRIF              IF1H_bit.no3
#define TMIF04            IF1H_bit.no7

#define WDTIMK            MK0L_bit.no0
#define LVIMK             MK0L_bit.no1
#define PMK0              MK0L_bit.no2
#define PMK1              MK0L_bit.no3
#define PMK2              MK0L_bit.no4
#define PMK3              MK0L_bit.no5
#define PMK4              MK0L_bit.no6
#define PMK5              MK0L_bit.no7

#define CSIMK20           MK0H_bit.no0
#define IICMK20           MK0H_bit.no0
#define STMK2             MK0H_bit.no0
#define CSIMK21           MK0H_bit.no1
#define IICMK21           MK0H_bit.no1
#define SRMK2             MK0H_bit.no1
#define SREMK2            MK0H_bit.no2
#define DMAMK0            MK0H_bit.no3
#define DMAMK1            MK0H_bit.no4
#define CSIMK00           MK0H_bit.no5
#define IICMK00           MK0H_bit.no5
#define STMK0             MK0H_bit.no5
#define CSIMK01           MK0H_bit.no6
#define IICMK01           MK0H_bit.no6
#define SRMK0             MK0H_bit.no6
#define SREMK0            MK0H_bit.no7
#define TMMK01H           MK0H_bit.no7

#define CSIMK10           MK1L_bit.no0
#define IICMK10           MK1L_bit.no0
#define STMK1             MK1L_bit.no0
#define CSIMK11           MK1L_bit.no1
#define IICMK11           MK1L_bit.no1
#define SRMK1             MK1L_bit.no1
#define SREMK1            MK1L_bit.no2
#define TMMK03H           MK1L_bit.no2
#define IICAMK0           MK1L_bit.no3
#define TMMK00            MK1L_bit.no4
#define TMMK01            MK1L_bit.no5
#define TMMK02            MK1L_bit.no6
#define TMMK03            MK1L_bit.no7

#define ADMK              MK1H_bit.no0
#define RTCMK             MK1H_bit.no1
#define ITMK              MK1H_bit.no2
#define KRMK              MK1H_bit.no3
#define TMMK04            MK1H_bit.no7

#define WDTIPR0           PR00L_bit.no0
#define LVIPR0            PR00L_bit.no1
#define PPR00             PR00L_bit.no2
#define PPR01             PR00L_bit.no3
#define PPR02             PR00L_bit.no4
#define PPR03             PR00L_bit.no5
#define PPR04             PR00L_bit.no6
#define PPR05             PR00L_bit.no7

#define CSIPR020          PR00H_bit.no0
#define IICPR020          PR00H_bit.no0
#define STPR02            PR00H_bit.no0
#define CSIPR021          PR00H_bit.no1
#define IICPR021          PR00H_bit.no1
#define SRPR02            PR00H_bit.no1
#define SREPR02           PR00H_bit.no2
#define DMAPR00           PR00H_bit.no3
#define DMAPR01           PR00H_bit.no4
#define CSIPR000          PR00H_bit.no5
#define IICPR000          PR00H_bit.no5
#define STPR00            PR00H_bit.no5
#define CSIPR001          PR00H_bit.no6
#define IICPR001          PR00H_bit.no6
#define SRPR00            PR00H_bit.no6
#define SREPR00           PR00H_bit.no7
#define TMPR001H          PR00H_bit.no7

#define CSIPR010          PR01L_bit.no0
#define IICPR010          PR01L_bit.no0
#define STPR01            PR01L_bit.no0
#define CSIPR011          PR01L_bit.no1
#define IICPR011          PR01L_bit.no1
#define SRPR01            PR01L_bit.no1
#define SREPR01           PR01L_bit.no2
#define TMPR003H          PR01L_bit.no2
#define IICAPR00          PR01L_bit.no3
#define TMPR000           PR01L_bit.no4
#define TMPR001           PR01L_bit.no5
#define TMPR002           PR01L_bit.no6
#define TMPR003           PR01L_bit.no7

#define ADPR0             PR01H_bit.no0
#define RTCPR0            PR01H_bit.no1
#define ITPR0             PR01H_bit.no2
#define KRPR0             PR01H_bit.no3
#define TMPR004           PR01H_bit.no7

#define WDTIPR1           PR10L_bit.no0
#define LVIPR1            PR10L_bit.no1
#define PPR10             PR10L_bit.no2
#define PPR11             PR10L_bit.no3
#define PPR12             PR10L_bit.no4
#define PPR13             PR10L_bit.no5
#define PPR14             PR10L_bit.no6
#define PPR15             PR10L_bit.no7

#define CSIPR120          PR10H_bit.no0
#define IICPR120          PR10H_bit.no0
#define STPR12            PR10H_bit.no0
#define CSIPR121          PR10H_bit.no1
#define IICPR121          PR10H_bit.no1
#define SRPR12            PR10H_bit.no1
#define SREPR12           PR10H_bit.no2
#define DMAPR10           PR10H_bit.no3
#define DMAPR11           PR10H_bit.no4
#define CSIPR100          PR10H_bit.no5
#define IICPR100          PR10H_bit.no5
#define STPR10            PR10H_bit.no5
#define CSIPR101          PR10H_bit.no6
#define IICPR101          PR10H_bit.no6
#define SRPR10            PR10H_bit.no6
#define SREPR10           PR10H_bit.no7
#define TMPR101H          PR10H_bit.no7

#define CSIPR110          PR11L_bit.no0
#define IICPR110          PR11L_bit.no0
#define STPR11            PR11L_bit.no0
#define CSIPR111          PR11L_bit.no1
#define IICPR111          PR11L_bit.no1
#define SRPR11            PR11L_bit.no1
#define SREPR11           PR11L_bit.no2
#define TMPR103H          PR11L_bit.no2
#define IICAPR10          PR11L_bit.no3
#define TMPR100           PR11L_bit.no4
#define TMPR101           PR11L_bit.no5
#define TMPR102           PR11L_bit.no6
#define TMPR103           PR11L_bit.no7

#define ADPR1             PR11H_bit.no0
#define RTCPR1            PR11H_bit.no1
#define ITPR1             PR11H_bit.no2
#define KRPR1             PR11H_bit.no3
#define TMPR104           PR11H_bit.no7

#define MAA               PMC_bit.no0

#pragma language=default

#endif /* __IAR_SYSTEMS_ICC__ */

#ifdef __IAR_SYSTEMS_ASM__

/*----------------------------------------------
 *       SFR declarations
 *--------------------------------------------*/

P0         DEFINE  0xFFF00
P1         DEFINE  0xFFF01
P2         DEFINE  0xFFF02
P3         DEFINE  0xFFF03
P4         DEFINE  0xFFF04
P5         DEFINE  0xFFF05
P6         DEFINE  0xFFF06
P7         DEFINE  0xFFF07
P12        DEFINE  0xFFF0C
P13        DEFINE  0xFFF0D
P14        DEFINE  0xFFF0E
SDR00      DEFINE  0xFFF10
SIO00      DEFINE  0xFFF10
TXD0       DEFINE  0xFFF10
SDR01      DEFINE  0xFFF12
RXD0       DEFINE  0xFFF12
SIO01      DEFINE  0xFFF12
TDR00      DEFINE  0xFFF18
TDR01      DEFINE  0xFFF1A
TDR01L     DEFINE  0xFFF1A
TDR01H     DEFINE  0xFFF1B
ADCR       DEFINE  0xFFF1E
ADCRH      DEFINE  0xFFF1F
PM0        DEFINE  0xFFF20
PM1        DEFINE  0xFFF21
PM2        DEFINE  0xFFF22
PM3        DEFINE  0xFFF23
PM4        DEFINE  0xFFF24
PM5        DEFINE  0xFFF25
PM6        DEFINE  0xFFF26
PM7        DEFINE  0xFFF27
PM12       DEFINE  0xFFF2C
PM14       DEFINE  0xFFF2E
ADM0       DEFINE  0xFFF30
ADS        DEFINE  0xFFF31
ADM1       DEFINE  0xFFF32
KRM        DEFINE  0xFFF37
EGP0       DEFINE  0xFFF38
EGN0       DEFINE  0xFFF39
EGP1       DEFINE  0xFFF3A
EGN1       DEFINE  0xFFF3B
SDR02      DEFINE  0xFFF44
SIO10      DEFINE  0xFFF44
TXD1       DEFINE  0xFFF44
SDR03      DEFINE  0xFFF46
RXD1       DEFINE  0xFFF46
SIO11      DEFINE  0xFFF46
SDR10      DEFINE  0xFFF48
SIO20      DEFINE  0xFFF48
TXD2       DEFINE  0xFFF48
SDR11      DEFINE  0xFFF4A
RXD2       DEFINE  0xFFF4A
SIO21      DEFINE  0xFFF4A
IICA0      DEFINE  0xFFF50
IICS0      DEFINE  0xFFF51
IICF0      DEFINE  0xFFF52
TDR02      DEFINE  0xFFF64
TDR03      DEFINE  0xFFF66
TDR03L     DEFINE  0xFFF66
TDR03H     DEFINE  0xFFF67
TDR04      DEFINE  0xFFF68
TDR05      DEFINE  0xFFF6A
TDR06      DEFINE  0xFFF6C
TDR07      DEFINE  0xFFF6E
ITMC       DEFINE  0xFFF90
SEC        DEFINE  0xFFF92
MIN        DEFINE  0xFFF93
HOUR       DEFINE  0xFFF94
WEEK       DEFINE  0xFFF95
DAY        DEFINE  0xFFF96
MONTH      DEFINE  0xFFF97
YEAR       DEFINE  0xFFF98
SUBCUD     DEFINE  0xFFF99
ALARMWM    DEFINE  0xFFF9A
ALARMWH    DEFINE  0xFFF9B
ALARMWW    DEFINE  0xFFF9C
RTCC0      DEFINE  0xFFF9D
RTCC1      DEFINE  0xFFF9E
CMC        DEFINE  0xFFFA0
CSC        DEFINE  0xFFFA1
OSTC       DEFINE  0xFFFA2
OSTS       DEFINE  0xFFFA3
CKC        DEFINE  0xFFFA4
CKS0       DEFINE  0xFFFA5
CKS1       DEFINE  0xFFFA6
RESF       DEFINE  0xFFFA8
LVIM       DEFINE  0xFFFA9
LVIS       DEFINE  0xFFFAA
WDTE       DEFINE  0xFFFAB
CRCIN      DEFINE  0xFFFAC
DSA0       DEFINE  0xFFFB0
DSA1       DEFINE  0xFFFB1
DRA0       DEFINE  0xFFFB2
DRA0L      DEFINE  0xFFFB2
DRA0H      DEFINE  0xFFFB3
DRA1       DEFINE  0xFFFB4
DRA1L      DEFINE  0xFFFB4
DRA1H      DEFINE  0xFFFB5
DBC0       DEFINE  0xFFFB6
DBC0L      DEFINE  0xFFFB6
DBC0H      DEFINE  0xFFFB7
DBC1       DEFINE  0xFFFB8
DBC1L      DEFINE  0xFFFB8
DBC1H      DEFINE  0xFFFB9
DMC0       DEFINE  0xFFFBA
DMC1       DEFINE  0xFFFBB
DRC0       DEFINE  0xFFFBC
DRC1       DEFINE  0xFFFBD
IF2        DEFINE  0xFFFD0
IF2L       DEFINE  0xFFFD0
IF2H       DEFINE  0xFFFD1
MK2        DEFINE  0xFFFD4
MK2L       DEFINE  0xFFFD4
MK2H       DEFINE  0xFFFD5
PR02       DEFINE  0xFFFD8
PR02L      DEFINE  0xFFFD8
PR02H      DEFINE  0xFFFD9
PR12       DEFINE  0xFFFDC
PR12L      DEFINE  0xFFFDC
PR12H      DEFINE  0xFFFDD
IF0        DEFINE  0xFFFE0
IF0L       DEFINE  0xFFFE0
IF0H       DEFINE  0xFFFE1
IF1        DEFINE  0xFFFE2
IF1L       DEFINE  0xFFFE2
IF1H       DEFINE  0xFFFE3
MK0        DEFINE  0xFFFE4
MK0L       DEFINE  0xFFFE4
MK0H       DEFINE  0xFFFE5
MK1        DEFINE  0xFFFE6
MK1L       DEFINE  0xFFFE6
MK1H       DEFINE  0xFFFE7
PR00       DEFINE  0xFFFE8
PR00L      DEFINE  0xFFFE8
PR00H      DEFINE  0xFFFE9
PR01       DEFINE  0xFFFEA
PR01L      DEFINE  0xFFFEA
PR01H      DEFINE  0xFFFEB
PR10       DEFINE  0xFFFEC
PR10L      DEFINE  0xFFFEC
PR10H      DEFINE  0xFFFED
PR11       DEFINE  0xFFFEE
PR11L      DEFINE  0xFFFEE
PR11H      DEFINE  0xFFFEF
MDAL       DEFINE  0xFFFF0
MULA       DEFINE  0xFFFF0
MDAH       DEFINE  0xFFFF2
MULB       DEFINE  0xFFFF2
MDBH       DEFINE  0xFFFF4
MULOH      DEFINE  0xFFFF4
MDBL       DEFINE  0xFFFF6
MULOL      DEFINE  0xFFFF6
PMC        DEFINE  0xFFFFE

#endif /* __IAR_SYSTEMS_ASM__ */

/*----------------------------------------------
 *       Interrupt vector addresses
 *--------------------------------------------*/

#define RST_vect                 (0x00)
#define INTDBG_vect              (0x02)
#define INTWDTI_vect             (0x04)
#define INTLVI_vect              (0x06)
#define INTP0_vect               (0x08)
#define INTP1_vect               (0x0A)
#define INTP2_vect               (0x0C)
#define INTP3_vect               (0x0E)
#define INTP4_vect               (0x10)
#define INTP5_vect               (0x12)
#define INTCSI20_vect            (0x14)
#define INTIIC20_vect            (0x14)
#define INTST2_vect              (0x14)
#define INTCSI21_vect            (0x16)
#define INTIIC21_vect            (0x16)
#define INTSR2_vect              (0x16)
#define INTSRE2_vect             (0x18)
#define INTDMA0_vect             (0x1A)
#define INTDMA1_vect             (0x1C)
#define INTCSI00_vect            (0x1E)
#define INTIIC00_vect            (0x1E)
#define INTST0_vect              (0x1E)
#define INTCSI01_vect            (0x20)
#define INTIIC01_vect            (0x20)
#define INTSR0_vect              (0x20)
#define INTSRE0_vect             (0x22)
#define INTTM01H_vect            (0x22)
#define INTCSI10_vect            (0x24)
#define INTIIC10_vect            (0x24)
#define INTST1_vect              (0x24)
#define INTCSI11_vect            (0x26)
#define INTIIC11_vect            (0x26)
#define INTSR1_vect              (0x26)
#define INTSRE1_vect             (0x28)
#define INTTM03H_vect            (0x28)
#define INTIICA0_vect            (0x2A)
#define INTTM00_vect             (0x2C)
#define INTTM01_vect             (0x2E)
#define INTTM02_vect             (0x30)
#define INTTM03_vect             (0x32)
#define INTAD_vect               (0x34)
#define INTRTC_vect              (0x36)
#define INTIT_vect               (0x38)
#define INTKR_vect               (0x3A)
#define INTTM04_vect             (0x42)
#define INTTM05_vect             (0x44)
#define INTTM06_vect             (0x46)
#define INTTM07_vect             (0x48)
#define INTP6_vect               (0x4A)
#define INTP7_vect               (0x4C)
#define INTP8_vect               (0x4E)
#define INTP9_vect               (0x50)
#define INTP10_vect              (0x52)
#define INTP11_vect              (0x54)
#define INTMD_vect               (0x5E)
#define INTFL_vect               (0x62)
#define BRK_I_vect               (0x7E)

/*----------------------------------------------
 *       Callt vector addresses
 *--------------------------------------------*/

#define CALLT_80_vect            (0x80)
#define CALLT_82_vect            (0x82)
#define CALLT_84_vect            (0x84)
#define CALLT_86_vect            (0x86)
#define CALLT_88_vect            (0x88)
#define CALLT_8A_vect            (0x8A)
#define CALLT_8C_vect            (0x8C)
#define CALLT_8E_vect            (0x8E)
#define CALLT_90_vect            (0x90)
#define CALLT_92_vect            (0x92)
#define CALLT_94_vect            (0x94)
#define CALLT_96_vect            (0x96)
#define CALLT_98_vect            (0x98)
#define CALLT_9A_vect            (0x9A)
#define CALLT_9C_vect            (0x9C)
#define CALLT_9E_vect            (0x9E)
#define CALLT_A0_vect            (0xA0)
#define CALLT_A2_vect            (0xA2)
#define CALLT_A4_vect            (0xA4)
#define CALLT_A6_vect            (0xA6)
#define CALLT_A8_vect            (0xA8)
#define CALLT_AA_vect            (0xAA)
#define CALLT_AC_vect            (0xAC)
#define CALLT_AE_vect            (0xAE)
#define CALLT_B0_vect            (0xB0)
#define CALLT_B2_vect            (0xB2)
#define CALLT_B4_vect            (0xB4)
#define CALLT_B6_vect            (0xB6)
#define CALLT_B8_vect            (0xB8)
#define CALLT_BA_vect            (0xBA)
#define CALLT_BC_vect            (0xBC)
#define CALLT_BE_vect            (0xBE)

#endif /* __IOR5F100LE_H__ */
