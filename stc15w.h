#ifndef STC15W_H
#define STC15W_H

__sfr __at (0x93) P0M1;
__sfr __at (0x94) P0M0;
__sfr __at (0x92) P1M0;
__sfr __at (0x93) P1M1;
__sfr __at (0x96) P2M0;
__sfr __at (0x95) P2M1;
__sfr __at (0xb2) P3M0;
__sfr __at (0xb1) P3M1;
__sfr __at (0xca) P5M0;
__sfr __at (0xc9) P5M1;

__sfr __at (0x8e) AUXR;
__sfr __at (0xd6) T2H;
__sfr __at (0xd7) T2L;

__sfr __at (0xc8) P5;
__sbit __at (0xc8) P5_0;
__sbit __at (0xc9) P5_1;
__sbit __at (0xca) P5_2;
__sbit __at (0xcb) P5_3;
__sbit __at (0xcc) P5_4;
__sbit __at (0xcd) P5_5;



#endif

