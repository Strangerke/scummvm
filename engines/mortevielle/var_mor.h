/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

/*
 * This code is based on original Mortville Manor DOS source code
 * Copyright (c) 1988-1989 Lankhor
 */

#ifndef MORTEVIELLE_VAR_H
#define MORTEVIELLE_VAR_H

#include "common/str.h"

namespace Mortevielle {

/*         Constantes, Types et Variables pour le

              M A N O I R   DE   M O R T E V I E L L E

                                                    ( version Nov 1988
                                                             +
                                                  musique & paroles Oct 88 )
                                                                             */

/*---------------------------------------------------------------------------*/
/*-------------------------     DEFINES    ----------------------------------*/
/*---------------------------------------------------------------------------*/

#define pred(type, v) (v - 1)
#define succ(type, v) (v + 1)
#define ord(v) ((int) v)

// TODO: Replace the following with proper implementations
#define mortevielle_exit(ret) error("Exit the game")
#define clrscr {}

/*---------------------------------------------------------------------------*/
/*-------------------------    CONSTANTS   ----------------------------------*/
/*---------------------------------------------------------------------------*/

const float freq0 = 1.19318e6;

const int seg_syst = 0x6fed;
const int segmou = 0x6f00;
const int segdon = 0x6c00;
const int adani = 0x7314;
const int adword = 0x4000;
const int adtroct = 0x406b;
const int adcfiec = 0x4300;
const int adbruit = 0x5cb0;/*2C00;*/
const int adbruit1 = 0x6924;/*3874;*/
const int adbruit2 = 0x6b30;/*3A80;*/
const int adbruit3 = 0x6ba6;/*3AF6;*/
const int adbruit5 = 0x3b50;
const int adson = 0x5cb0;/*2C00;*/
const int adson2 = 0x60b0;/*3000;*/
const int offsetb1 = 6;
const int offsetb2 = 4;
const int offsetb3 = 6;

const int null = 255;

const int tempo_mus = 71;
const int tempo_bruit = 78;
const int tempo_f = 80;
const int tempo_m = 89;

const int ti1 = 410;
const int ti2 = 250;
const int maxti = 7975;
const int maxtd = 600;
const int max_rect = 14;

const int c_repon = 0;
const int c_st41 = 186;
const int c_tparler = 247;
const int c_paroles = 292;
const int c_tmlieu = 435;
const int c_dialpre = 456;
const int c_action = 476;
const int c_saction = 497;
const int c_dis = 502;
const int c_fin = 510;    /*  =>   n'existe pas  ; si !! */

const int arega = 0;
const int asoul = 154;
const int aouvr = 282;
const int achai = 387;
const int acha = 492;
const int arcf = 1272;
const int arep = 1314;
const int amzon = 1650;
const int fleche = 1758;

const int no_choice = 0;
const int invent = 1;
const int depla = 2;
const int action = 3;
const int saction = 4;
const int discut = 5;
const int fichier = 6;
const int sauve = 7;
const int charge = 8;

const int attacher = 0x301;
const int attendre = 0x302;
const int defoncer = 0x303;
const int dormir = 0x304;
const int ecouter = 0x305;
const int entrer = 0x306;
const int fermer = 0x307;
const int fouiller = 0x308;
const int frapper = 0x309;
const int gratter = 0x30a;
const int lire = 0x30b;
const int manger = 0x30c;
const int mettre = 0x30d;
const int ouvrir = 0x30e;
const int prendre = 0x30f;
const int regarder = 0x310;
const int sentir = 0x311;
const int sonder = 0x312;
const int sortir = 0x313;
const int soulever = 0x314;
const int tourner = 0x315;

const int scacher = 0x401;
const int sfouiller = 0x402;
const int slire = 0x403;
const int sposer = 0x404;
const int sregarder = 0x405;

const int max_patt = 20;

extern const byte tabdbc[18];
extern const byte tabdph[16];
extern const byte typcon[26];
extern const byte intcon[26];
extern const byte tnocon[364];

extern const byte don[9][5];

extern const char *fic[3];

extern const byte addv[2];

extern const char recom[];

extern const char f3[];
extern const char f8[];

extern const byte rang[16];


/*---------------------------------------------------------------------------*/
/*--------------------------------   TYPES   --------------------------------*/
/*---------------------------------------------------------------------------*/

struct sav_chaine {
	int conf;
	char pourc[11];
	char teauto[43];
	char sjer[31];
	int mlieu, iboul, ibag, icave, ivier, ipuit;
	int derobj, iloic, icryp;
	bool ipre;
	char heure;
};
struct registres {
	int ax, bx, cx, dx, bp, si, di, ds, es, flags;
};

struct ind {
	int indis;
	byte point;
};

typedef int word1;
struct chariot {
	int val,
	        code,
	        acc,
	        freq,
	        rep;
};

struct doublet {
	byte x, y;
};

struct rectangle {
	int x1, x2, y1, y2;
	bool etat;
};

struct pattern {
	byte tay, tax;
	byte des[max_patt+1][max_patt+1];
};


struct nhom {
	byte n;     /* numero entre 0 et 32 */
	byte hom[4];
};

typedef nhom t_nhom[16];

struct t_pcga {
	byte p;
	nhom a[16];
};

/*---------------------------------------------------------------------------*/
/*------------------------------     ENUMS     ------------------------------*/
/*---------------------------------------------------------------------------*/

enum GraphicModes { ams = 0, cga = 1, ega = 2, her = 3, tan = 4 };

/*---------------------------------------------------------------------------*/
/*------------------------------   VARIABLES   ------------------------------*/
/*---------------------------------------------------------------------------*/

extern bool blo,
        bh1,
        bf1,
        bh2,
        bh4,
        bf4,
        bh5,
        bh6,
        bh8,
        bt3,
        bt7,
        bh9,

        sonoff,
        main1,
        choisi,
        test0,
        f2_all,
        imen,
        cache,
        iesc,
        perdu,
        col,
        syn,
        fouil,
        zuul,
        tesok,
        obpart,
        okdes,
        solu,
        arret,
        anyone,
        brt,
        rect,
        rech_cfiec,
        active_menu;


extern int x,
        y,
        t,
        vj,
        li,
        vh,
        vm,
        jh,
        mh,
        cs,
        gd,                /*  Gd = graph device  */
        hdb,
        hfb,
        heu,
        jou,
        key,
        min,
        num,
        max,
        res,
        ment,
        haut,
        caff,
        maff,
        crep,
        ades,
        iouv,
        inei,
        ctrm,
        dobj,
        msg3,
        msg4,
        mlec,
        newgd,
        c_zzz,
        mchai,
        menup,
        ipers,
        ledeb,
        lefin,
        mpers,
        mnumo,
        xprec,
        yprec,
        perdep,
        prebru,
        typlec,
        num_ph,
        xwhere,
        ywhere,
        numpal,
        lderobj,
        nb_word,
        ptr_oct,
        k_tempo,
        ptr_tcph,
        ptr_word,
        color_txt;

extern int t_cph[6401];
extern byte tabdon[4001];
/*   t_dxx  : array[0..121] of int;*/
extern Common::String stpou;                               /* donne le % d'indices */
extern byte is;
extern char mode;
extern Common::String al_mess,
       err_mess,
       ind_mess,
       al_mess2;

extern int invt[8];
extern int nbrep[8];
extern int nbrepm[8];
extern int disc[8];
extern int msg[5];
extern int depl[7];
extern Common::String inv[9];
extern Common::String dep[8];
extern Common::String act[22];
extern Common::String self_[6];
extern Common::String dis[9];
extern char touv[7];
extern sav_chaine s, s1;
extern byte bufcha[391];

extern byte lettres[7][24];

extern byte palher[16];

extern int t_mot[maxti + 1];
extern int tay_tchar;
extern ind t_rec[maxtd + 1];
//file<ind> sauv_t;
//untyped_file fibyte;
extern byte v_lieu[8][25];
extern int l[108];
extern int tbi[256];
extern chariot c1, c2, c3;
extern float addfix;
extern t_pcga palsav[91];
extern doublet tabpal[91][16];
extern t_pcga palcga[91];
extern pattern tpt[15];

/*---------------------------------------------------------------------------*/
/*-------------------   PROCEDURES  AND  FONCTIONS   ------------------------*/
/*---------------------------------------------------------------------------*/

void hirs();
void affcar(int gd, int x, int y, int coul, int chr);
void putpix(int gd, int x, int y, int coul);

} // End of namespace Mortevielle

#endif
