/*-------------------------------------------------------------------------
 *      Declarations of extended SFR registers for RL78 microcontroller R5F100LE.
 *
 *      This file can be used by both the RL78,
 *      Assembler, ARL78, and the C/C++ compiler, ICCRL78.
 *
 *      This header file is generated from the device file:
 *          DR5F100LE.DVF
 *          Copyright(C) 2011 Renesas
 *          Format version V3.00, File version E1.00d
 *-------------------------------------------------------------------------*/

#ifndef __IOR5F100LE_EXT_H__
#define __IOR5F100LE_EXT_H__

#if !defined(__ARL78__) && !defined(__ICCRL78__)
  #error "IOR5F100LE_EXT.H file for use with RL78 Assembler or Compiler only"
#endif

#if defined(__ARL78__)
  #if __CORE__ != __RL78_1__
    #error "IOR5F100LE_EXT.H file for use with ARL78 option --core rl78_1 only"
  #endif
#endif
#if defined(__ICCRL78__)
  #if __CORE__ != __RL78_1__
    #error "IOR5F100LE_EXT.H file for use with ICCRL78 option --core rl78_1 only"
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
 *       Extended SFR declarations
 *--------------------------------------------*/

__near __no_init volatile union { unsigned char ADM2; __BITS8 ADM2_bit; } @ 0xF0010;
__near __no_bit_access __no_init volatile unsigned char ADUL @ 0xF0011;
__near __no_bit_access __no_init volatile unsigned char ADLL @ 0xF0012;
__near __no_bit_access __no_init volatile unsigned char ADTES @ 0xF0013;
__near __no_init volatile union { unsigned char PU0; __BITS8 PU0_bit; } @ 0xF0030;
__near __no_init volatile union { unsigned char PU1; __BITS8 PU1_bit; } @ 0xF0031;
__near __no_init volatile union { unsigned char PU3; __BITS8 PU3_bit; } @ 0xF0033;
__near __no_init volatile union { unsigned char PU4; __BITS8 PU4_bit; } @ 0xF0034;
__near __no_init volatile union { unsigned char PU5; __BITS8 PU5_bit; } @ 0xF0035;
__near __no_init volatile union { unsigned char PU7; __BITS8 PU7_bit; } @ 0xF0037;
__near __no_init volatile union { unsigned char PU12; __BITS8 PU12_bit; } @ 0xF003C;
__near __no_init volatile union { unsigned char PU14; __BITS8 PU14_bit; } @ 0xF003E;
__near __no_init volatile union { unsigned char PIM0; __BITS8 PIM0_bit; } @ 0xF0040;
__near __no_init volatile union { unsigned char PIM1; __BITS8 PIM1_bit; } @ 0xF0041;
__near __no_init volatile union { unsigned char PIM5; __BITS8 PIM5_bit; } @ 0xF0045;
__near __no_init volatile union { unsigned char POM0; __BITS8 POM0_bit; } @ 0xF0050;
__near __no_init volatile union { unsigned char POM1; __BITS8 POM1_bit; } @ 0xF0051;
__near __no_init volatile union { unsigned char POM5; __BITS8 POM5_bit; } @ 0xF0055;
__near __no_init volatile union { unsigned char POM7; __BITS8 POM7_bit; } @ 0xF0057;
__near __no_init volatile union { unsigned char PMC0; __BITS8 PMC0_bit; } @ 0xF0060;
__near __no_init volatile union { unsigned char PMC12; __BITS8 PMC12_bit; } @ 0xF006C;
__near __no_init volatile union { unsigned char PMC14; __BITS8 PMC14_bit; } @ 0xF006E;
__near __no_init volatile union { unsigned char NFEN0; __BITS8 NFEN0_bit; } @ 0xF0070;
__near __no_init volatile union { unsigned char NFEN1; __BITS8 NFEN1_bit; } @ 0xF0071;
__near __no_init volatile union { unsigned char ISC; __BITS8 ISC_bit; } @ 0xF0073;
__near __no_bit_access __no_init volatile unsigned char TIS0 @ 0xF0074;
__near __no_bit_access __no_init volatile unsigned char ADPC @ 0xF0076;
__near __no_bit_access __no_init volatile unsigned char PIOR @ 0xF0077;
__near __no_bit_access __no_init volatile unsigned char IAWCTL @ 0xF0078;
__near __no_init volatile union { unsigned char GDIDIS; __BITS8 GDIDIS_bit; } @ 0xF007D;
__near __no_init volatile union { unsigned char DFLCTL; __BITS8 DFLCTL_bit; } @ 0xF0090;
__near __no_bit_access __no_init volatile unsigned char HIOTRM @ 0xF00A0;
__near __no_bit_access __no_init volatile unsigned char HOCODIV @ 0xF00A8;
__near __no_bit_access __no_init volatile const unsigned char TEMPCAL0 @ 0xF00AC;
__near __no_bit_access __no_init volatile const unsigned char TEMPCAL1 @ 0xF00AD;
__near __no_bit_access __no_init volatile const unsigned char TEMPCAL2 @ 0xF00AE;
__near __no_bit_access __no_init volatile const unsigned char TEMPCAL3 @ 0xF00AF;
__near __no_bit_access __no_init volatile unsigned short MDCL @ 0xF00E0;
__near __no_bit_access __no_init volatile unsigned short MDCH @ 0xF00E2;
__near __no_init volatile union { unsigned char MDUC; __BITS8 MDUC_bit; } @ 0xF00E8;
__near __no_init volatile union { unsigned char PER0; __BITS8 PER0_bit; } @ 0xF00F0;
__near __no_bit_access __no_init volatile unsigned char OSMC @ 0xF00F3;
__near __no_init volatile union { unsigned char RMC; __BITS8 RMC_bit; } @ 0xF00F4;
__near __no_init volatile union { unsigned char RPECTL; __BITS8 RPECTL_bit; } @ 0xF00F5;
__near __no_bit_access __no_init volatile const unsigned char BCDADJ @ 0xF00FE;
__near __no_bit_access __no_init volatile const union { unsigned short SSR00; struct { unsigned char SSR00L; }; } @ 0xF0100;
__near __no_bit_access __no_init volatile const union { unsigned short SSR01; struct { unsigned char SSR01L; }; } @ 0xF0102;
__near __no_bit_access __no_init volatile const union { unsigned short SSR02; struct { unsigned char SSR02L; }; } @ 0xF0104;
__near __no_bit_access __no_init volatile const union { unsigned short SSR03; struct { unsigned char SSR03L; }; } @ 0xF0106;
__near __no_bit_access __no_init volatile union { unsigned short SIR00; struct { unsigned char SIR00L; }; } @ 0xF0108;
__near __no_bit_access __no_init volatile union { unsigned short SIR01; struct { unsigned char SIR01L; }; } @ 0xF010A;
__near __no_bit_access __no_init volatile union { unsigned short SIR02; struct { unsigned char SIR02L; }; } @ 0xF010C;
__near __no_bit_access __no_init volatile union { unsigned short SIR03; struct { unsigned char SIR03L; }; } @ 0xF010E;
__near __no_bit_access __no_init volatile unsigned short SMR00 @ 0xF0110;
__near __no_bit_access __no_init volatile unsigned short SMR01 @ 0xF0112;
__near __no_bit_access __no_init volatile unsigned short SMR02 @ 0xF0114;
__near __no_bit_access __no_init volatile unsigned short SMR03 @ 0xF0116;
__near __no_bit_access __no_init volatile unsigned short SCR00 @ 0xF0118;
__near __no_bit_access __no_init volatile unsigned short SCR01 @ 0xF011A;
__near __no_bit_access __no_init volatile unsigned short SCR02 @ 0xF011C;
__near __no_bit_access __no_init volatile unsigned short SCR03 @ 0xF011E;
__near __no_init volatile const union { unsigned short SE0; struct { union { unsigned char SE0L; __BITS8 SE0L_bit; }; }; } @ 0xF0120;
__near __no_init volatile union { unsigned short SS0; struct { union { unsigned char SS0L; __BITS8 SS0L_bit; }; }; } @ 0xF0122;
__near __no_init volatile union { unsigned short ST0; struct { union { unsigned char ST0L; __BITS8 ST0L_bit; }; }; } @ 0xF0124;
__near __no_bit_access __no_init volatile union { unsigned short SPS0; struct { unsigned char SPS0L; }; } @ 0xF0126;
__near __no_bit_access __no_init volatile unsigned short SO0 @ 0xF0128;
__near __no_init volatile union { unsigned short SOE0; struct { union { unsigned char SOE0L; __BITS8 SOE0L_bit; }; }; } @ 0xF012A;
__near __no_bit_access __no_init volatile union { unsigned short SOL0; struct { unsigned char SOL0L; }; } @ 0xF0134;
__near __no_bit_access __no_init volatile union { unsigned short SSC0; struct { unsigned char SSC0L; }; } @ 0xF0138;
__near __no_bit_access __no_init volatile const union { unsigned short SSR10; struct { unsigned char SSR10L; }; } @ 0xF0140;
__near __no_bit_access __no_init volatile const union { unsigned short SSR11; struct { unsigned char SSR11L; }; } @ 0xF0142;
__near __no_bit_access __no_init volatile union { unsigned short SIR10; struct { unsigned char SIR10L; }; } @ 0xF0148;
__near __no_bit_access __no_init volatile union { unsigned short SIR11; struct { unsigned char SIR11L; }; } @ 0xF014A;
__near __no_bit_access __no_init volatile unsigned short SMR10 @ 0xF0150;
__near __no_bit_access __no_init volatile unsigned short SMR11 @ 0xF0152;
__near __no_bit_access __no_init volatile unsigned short SCR10 @ 0xF0158;
__near __no_bit_access __no_init volatile unsigned short SCR11 @ 0xF015A;
__near __no_init volatile const union { unsigned short SE1; struct { union { unsigned char SE1L; __BITS8 SE1L_bit; }; }; } @ 0xF0160;
__near __no_init volatile union { unsigned short SS1; struct { union { unsigned char SS1L; __BITS8 SS1L_bit; }; }; } @ 0xF0162;
__near __no_init volatile union { unsigned short ST1; struct { union { unsigned char ST1L; __BITS8 ST1L_bit; }; }; } @ 0xF0164;
__near __no_bit_access __no_init volatile union { unsigned short SPS1; struct { unsigned char SPS1L; }; } @ 0xF0166;
__near __no_bit_access __no_init volatile unsigned short SO1 @ 0xF0168;
__near __no_init volatile union { unsigned short SOE1; struct { union { unsigned char SOE1L; __BITS8 SOE1L_bit; }; }; } @ 0xF016A;
__near __no_bit_access __no_init volatile union { unsigned short SOL1; struct { unsigned char SOL1L; }; } @ 0xF0174;
__near __no_bit_access __no_init volatile const unsigned short TCR00 @ 0xF0180;
__near __no_bit_access __no_init volatile const unsigned short TCR01 @ 0xF0182;
__near __no_bit_access __no_init volatile const unsigned short TCR02 @ 0xF0184;
__near __no_bit_access __no_init volatile const unsigned short TCR03 @ 0xF0186;
__near __no_bit_access __no_init volatile const unsigned short TCR04 @ 0xF0188;
__near __no_bit_access __no_init volatile const unsigned short TCR05 @ 0xF018A;
__near __no_bit_access __no_init volatile const unsigned short TCR06 @ 0xF018C;
__near __no_bit_access __no_init volatile const unsigned short TCR07 @ 0xF018E;
__near __no_bit_access __no_init volatile unsigned short TMR00 @ 0xF0190;
__near __no_bit_access __no_init volatile unsigned short TMR01 @ 0xF0192;
__near __no_bit_access __no_init volatile unsigned short TMR02 @ 0xF0194;
__near __no_bit_access __no_init volatile unsigned short TMR03 @ 0xF0196;
__near __no_bit_access __no_init volatile unsigned short TMR04 @ 0xF0198;
__near __no_bit_access __no_init volatile unsigned short TMR05 @ 0xF019A;
__near __no_bit_access __no_init volatile unsigned short TMR06 @ 0xF019C;
__near __no_bit_access __no_init volatile unsigned short TMR07 @ 0xF019E;
__near __no_bit_access __no_init volatile const union { unsigned short TSR00; struct { unsigned char TSR00L; }; } @ 0xF01A0;
__near __no_bit_access __no_init volatile const union { unsigned short TSR01; struct { unsigned char TSR01L; }; } @ 0xF01A2;
__near __no_bit_access __no_init volatile const union { unsigned short TSR02; struct { unsigned char TSR02L; }; } @ 0xF01A4;
__near __no_bit_access __no_init volatile const union { unsigned short TSR03; struct { unsigned char TSR03L; }; } @ 0xF01A6;
__near __no_bit_access __no_init volatile const union { unsigned short TSR04; struct { unsigned char TSR04L; }; } @ 0xF01A8;
__near __no_bit_access __no_init volatile const union { unsigned short TSR05; struct { unsigned char TSR05L; }; } @ 0xF01AA;
__near __no_bit_access __no_init volatile const union { unsigned short TSR06; struct { unsigned char TSR06L; }; } @ 0xF01AC;
__near __no_bit_access __no_init volatile const union { unsigned short TSR07; struct { unsigned char TSR07L; }; } @ 0xF01AE;
__near __no_init volatile const union { unsigned short TE0; struct { union { unsigned char TE0L; __BITS8 TE0L_bit; }; }; } @ 0xF01B0;
__near __no_init volatile union { unsigned short TS0; struct { union { unsigned char TS0L; __BITS8 TS0L_bit; }; }; } @ 0xF01B2;
__near __no_init volatile union { unsigned short TT0; struct { union { unsigned char TT0L; __BITS8 TT0L_bit; }; }; } @ 0xF01B4;
__near __no_bit_access __no_init volatile unsigned short TPS0 @ 0xF01B6;
__near __no_bit_access __no_init volatile union { unsigned short TO0; struct { unsigned char TO0L; }; } @ 0xF01B8;
__near __no_init volatile union { unsigned short TOE0; struct { union { unsigned char TOE0L; __BITS8 TOE0L_bit; }; }; } @ 0xF01BA;
__near __no_bit_access __no_init volatile union { unsigned short TOL0; struct { unsigned char TOL0L; }; } @ 0xF01BC;
__near __no_bit_access __no_init volatile union { unsigned short TOM0; struct { unsigned char TOM0L; }; } @ 0xF01BE;
__near __no_init volatile union { unsigned char IICCTL00; __BITS8 IICCTL00_bit; } @ 0xF0230;
__near __no_init volatile union { unsigned char IICCTL01; __BITS8 IICCTL01_bit; } @ 0xF0231;
__near __no_bit_access __no_init volatile unsigned char IICWL0 @ 0xF0232;
__near __no_bit_access __no_init volatile unsigned char IICWH0 @ 0xF0233;
__near __no_bit_access __no_init volatile unsigned char SVA0 @ 0xF0234;
__near __no_init volatile union { unsigned char CRC0CTL; __BITS8 CRC0CTL_bit; } @ 0xF02F0;
__near __no_bit_access __no_init volatile unsigned short PGCRCL @ 0xF02F2;
__near __no_bit_access __no_init volatile unsigned short CRCD @ 0xF02FA;

/*----------------------------------------------
 *       Extended SFR bit declarations
 *--------------------------------------------*/

#define ADTYP             ADM2_bit.no0
#define AWC               ADM2_bit.no2
#define ADRCK             ADM2_bit.no3

#define DFLEN             DFLCTL_bit.no0

#define DIVST             MDUC_bit.no0
#define MACSF             MDUC_bit.no1
#define MACOF             MDUC_bit.no2
#define MDSM              MDUC_bit.no3
#define MACMODE           MDUC_bit.no6
#define DIVMODE           MDUC_bit.no7

#define TAU0EN            PER0_bit.no0
#define SAU0EN            PER0_bit.no2
#define SAU1EN            PER0_bit.no3
#define IICA0EN           PER0_bit.no4
#define ADCEN             PER0_bit.no5
#define RTCEN             PER0_bit.no7

#define WDVOL             RMC_bit.no7

#define RPEF              RPECTL_bit.no0
#define RPERDIS           RPECTL_bit.no7

#define SPT0              IICCTL00_bit.no0
#define STT0              IICCTL00_bit.no1
#define ACKE0             IICCTL00_bit.no2
#define WTIM0             IICCTL00_bit.no3
#define SPIE0             IICCTL00_bit.no4
#define WREL0             IICCTL00_bit.no5
#define LREL0             IICCTL00_bit.no6
#define IICE0             IICCTL00_bit.no7

#define PRS0              IICCTL01_bit.no0
#define DFC0              IICCTL01_bit.no2
#define SMC0              IICCTL01_bit.no3
#define DAD0              IICCTL01_bit.no4
#define CLD0              IICCTL01_bit.no5
#define WUP0              IICCTL01_bit.no7

#define CRC0EN            CRC0CTL_bit.no7

#pragma language=default

#endif /* __IAR_SYSTEMS_ICC__ */

#ifdef __IAR_SYSTEMS_ASM__

/*----------------------------------------------
 *       Extended SFR declarations
 *--------------------------------------------*/

ADM2       DEFINE  0xF0010
ADUL       DEFINE  0xF0011
ADLL       DEFINE  0xF0012
ADTES      DEFINE  0xF0013
PU0        DEFINE  0xF0030
PU1        DEFINE  0xF0031
PU3        DEFINE  0xF0033
PU4        DEFINE  0xF0034
PU5        DEFINE  0xF0035
PU7        DEFINE  0xF0037
PU12       DEFINE  0xF003C
PU14       DEFINE  0xF003E
PIM0       DEFINE  0xF0040
PIM1       DEFINE  0xF0041
PIM5       DEFINE  0xF0045
POM0       DEFINE  0xF0050
POM1       DEFINE  0xF0051
POM5       DEFINE  0xF0055
POM7       DEFINE  0xF0057
PMC0       DEFINE  0xF0060
PMC12      DEFINE  0xF006C
PMC14      DEFINE  0xF006E
NFEN0      DEFINE  0xF0070
NFEN1      DEFINE  0xF0071
ISC        DEFINE  0xF0073
TIS0       DEFINE  0xF0074
ADPC       DEFINE  0xF0076
PIOR       DEFINE  0xF0077
IAWCTL     DEFINE  0xF0078
GDIDIS     DEFINE  0xF007D
DFLCTL     DEFINE  0xF0090
HIOTRM     DEFINE  0xF00A0
HOCODIV    DEFINE  0xF00A8
TEMPCAL0   DEFINE  0xF00AC
TEMPCAL1   DEFINE  0xF00AD
TEMPCAL2   DEFINE  0xF00AE
TEMPCAL3   DEFINE  0xF00AF
MDCL       DEFINE  0xF00E0
MDCH       DEFINE  0xF00E2
MDUC       DEFINE  0xF00E8
PER0       DEFINE  0xF00F0
OSMC       DEFINE  0xF00F3
RMC        DEFINE  0xF00F4
RPECTL     DEFINE  0xF00F5
BCDADJ     DEFINE  0xF00FE
SSR00      DEFINE  0xF0100
SSR00L     DEFINE  0xF0100
SSR01      DEFINE  0xF0102
SSR01L     DEFINE  0xF0102
SSR02      DEFINE  0xF0104
SSR02L     DEFINE  0xF0104
SSR03      DEFINE  0xF0106
SSR03L     DEFINE  0xF0106
SIR00      DEFINE  0xF0108
SIR00L     DEFINE  0xF0108
SIR01      DEFINE  0xF010A
SIR01L     DEFINE  0xF010A
SIR02      DEFINE  0xF010C
SIR02L     DEFINE  0xF010C
SIR03      DEFINE  0xF010E
SIR03L     DEFINE  0xF010E
SMR00      DEFINE  0xF0110
SMR01      DEFINE  0xF0112
SMR02      DEFINE  0xF0114
SMR03      DEFINE  0xF0116
SCR00      DEFINE  0xF0118
SCR01      DEFINE  0xF011A
SCR02      DEFINE  0xF011C
SCR03      DEFINE  0xF011E
SE0        DEFINE  0xF0120
SE0L       DEFINE  0xF0120
SS0        DEFINE  0xF0122
SS0L       DEFINE  0xF0122
ST0        DEFINE  0xF0124
ST0L       DEFINE  0xF0124
SPS0       DEFINE  0xF0126
SPS0L      DEFINE  0xF0126
SO0        DEFINE  0xF0128
SOE0       DEFINE  0xF012A
SOE0L      DEFINE  0xF012A
SOL0       DEFINE  0xF0134
SOL0L      DEFINE  0xF0134
SSC0       DEFINE  0xF0138
SSC0L      DEFINE  0xF0138
SSR10      DEFINE  0xF0140
SSR10L     DEFINE  0xF0140
SSR11      DEFINE  0xF0142
SSR11L     DEFINE  0xF0142
SIR10      DEFINE  0xF0148
SIR10L     DEFINE  0xF0148
SIR11      DEFINE  0xF014A
SIR11L     DEFINE  0xF014A
SMR10      DEFINE  0xF0150
SMR11      DEFINE  0xF0152
SCR10      DEFINE  0xF0158
SCR11      DEFINE  0xF015A
SE1        DEFINE  0xF0160
SE1L       DEFINE  0xF0160
SS1        DEFINE  0xF0162
SS1L       DEFINE  0xF0162
ST1        DEFINE  0xF0164
ST1L       DEFINE  0xF0164
SPS1       DEFINE  0xF0166
SPS1L      DEFINE  0xF0166
SO1        DEFINE  0xF0168
SOE1       DEFINE  0xF016A
SOE1L      DEFINE  0xF016A
SOL1       DEFINE  0xF0174
SOL1L      DEFINE  0xF0174
TCR00      DEFINE  0xF0180
TCR01      DEFINE  0xF0182
TCR02      DEFINE  0xF0184
TCR03      DEFINE  0xF0186
TCR04      DEFINE  0xF0188
TCR05      DEFINE  0xF018A
TCR06      DEFINE  0xF018C
TCR07      DEFINE  0xF018E
TMR00      DEFINE  0xF0190
TMR01      DEFINE  0xF0192
TMR02      DEFINE  0xF0194
TMR03      DEFINE  0xF0196
TMR04      DEFINE  0xF0198
TMR05      DEFINE  0xF019A
TMR06      DEFINE  0xF019C
TMR07      DEFINE  0xF019E
TSR00      DEFINE  0xF01A0
TSR00L     DEFINE  0xF01A0
TSR01      DEFINE  0xF01A2
TSR01L     DEFINE  0xF01A2
TSR02      DEFINE  0xF01A4
TSR02L     DEFINE  0xF01A4
TSR03      DEFINE  0xF01A6
TSR03L     DEFINE  0xF01A6
TSR04      DEFINE  0xF01A8
TSR04L     DEFINE  0xF01A8
TSR05      DEFINE  0xF01AA
TSR05L     DEFINE  0xF01AA
TSR06      DEFINE  0xF01AC
TSR06L     DEFINE  0xF01AC
TSR07      DEFINE  0xF01AE
TSR07L     DEFINE  0xF01AE
TE0        DEFINE  0xF01B0
TE0L       DEFINE  0xF01B0
TS0        DEFINE  0xF01B2
TS0L       DEFINE  0xF01B2
TT0        DEFINE  0xF01B4
TT0L       DEFINE  0xF01B4
TPS0       DEFINE  0xF01B6
TO0        DEFINE  0xF01B8
TO0L       DEFINE  0xF01B8
TOE0       DEFINE  0xF01BA
TOE0L      DEFINE  0xF01BA
TOL0       DEFINE  0xF01BC
TOL0L      DEFINE  0xF01BC
TOM0       DEFINE  0xF01BE
TOM0L      DEFINE  0xF01BE
IICCTL00   DEFINE  0xF0230
IICCTL01   DEFINE  0xF0231
IICWL0     DEFINE  0xF0232
IICWH0     DEFINE  0xF0233
SVA0       DEFINE  0xF0234
CRC0CTL    DEFINE  0xF02F0
PGCRCL     DEFINE  0xF02F2
CRCD       DEFINE  0xF02FA

#endif /* __IAR_SYSTEMS_ASM__ */

#endif /* __IOR5F100LE_EXT_H__ */
