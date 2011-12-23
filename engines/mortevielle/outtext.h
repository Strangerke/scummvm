str255 delig;
const array<0,31,byte> tabdr
      = {{  32, 101, 115,  97, 114, 105, 110,
          117, 116, 111, 108,  13, 100,  99,
          112, 109,  46, 118, 130,  39, 102,
           98,  44, 113, 104, 103,  33,  76,
           85, 106,  30,  31 }};


const array<0,31,byte> tab30
      = {{   69,  67,  74, 138, 133, 120,  77, 122,
          121,  68,  65,  63,  73,  80,  83,  82,
          156,  45,  58,  79,  49,  86,  78,  84,
           71,  81,  64,  66, 135,  34, 136,  91 }};



const array<0,31,byte> tab31
      = {{  93,  47,  48,  53,  50,  70, 124,  75,
           72, 147, 140, 150, 151,  57,  56,  51,
          107, 139,  55,  89, 131,  37,  54,  88,
          119,   0,   0,   0,   0,   0,   0,   0 }};

void deline( integer num , phrase& l , integer& tl );

static void cinq_huit( char& c, integer& ind, byte& pt, boolean& the_end)
   {
           const array<0,31,char> rap
         = {{ ',', ':', '@', '!', '?', '-', '�',
            '�', '�', '�', '�', '�', '�', '/',
            '�', '�', '�', '\47', '�', '"', '�',
            '�', '0', '1', '2', '3', '4', '5',
            '6', '7', '8', '9'}};
         integer oct,ocd;

            /* 5-8 */
     oct=t_mot[ind];
     oct=(cardinal)(oct << (16-pt)) >> (16-pt);
     if (pt<6) 
        {
          ind=ind+1;
          oct=oct << (5-pt);
          pt=pt+11;
          oct=oct | ((cardinal)t_mot[ind] >> pt);
        }
      else
        {
          pt=pt-5;
          oct=(cardinal)oct >> pt;
        }

     switch (oct) {
                  case 11 : {
                         c= '$';
                         the_end= true;
                       }
                       break;
               case 30:case 31 : {
                         ocd=t_mot[ind];
                         ocd=(cardinal)(ocd << (16-pt)) >> (16-pt);
                         if (pt<6) 
                            {
                              ind=ind+1;
                              ocd=ocd << (5-pt);
                              pt=pt+11;
                              ocd=ocd | ((cardinal)t_mot[ind] >> pt);
                            }
                          else
                            {
                              pt=pt-5;
                              ocd=(cardinal)ocd >> pt;
                            }
                          if (oct==30)  c=chr(tab30[ocd]);
                                    else c=chr(tab31[ocd]);
                          if (c=='\0') 
                             {
                               the_end=true;
                               c='#';
                             }
                        }
                        break;
              default: c=chr(tabdr[oct]);
            }
   }              /* 5-8 */

void deline( integer num , phrase& l , integer& tl )
      {
            integer i,j,ts;
            char let;
             byte ps, k;
            boolean the_end;

              /* DETEX */
        /*debug('  => DeLine');*/
        delig="";
        ts= t_rec[num].indis;
        ps= t_rec[num].point;
        i=ts;
        tl=1;
        j=1;
        k=ps;
        the_end=false;
        do {
          cinq_huit(let,i,k, the_end);
          l[j]=let;
          if (j<254)  delig=delig+let;
          j=j+1;
        } while  (!the_end);
        tl=j-1;
        if (tl<255)  delig=copy(delig,1,tl-1);       /* enleve le $ */
      }       /* DETEX */


void afftex( phrase ch, integer x,integer y,integer dx,integer dy, integer typ);


static integer l_motsuiv(integer p, phrase& ch, integer& tab)
  {
        integer c;

    integer l_motsuiv_result;
    c=p;
    while (! (set::of(' ','$','@', eos).has(ch[p])))  p=p+1;
    l_motsuiv_result=tab*(p-c);
    return l_motsuiv_result;
  }

void afftex( phrase ch, integer x,integer y,integer dx,integer dy, integer typ)
  {
        boolean the_end;
        char touch;
        integer xf,yf;
        integer xc,yc;
        integer tab, p;
        varying_string<255> s;
        integer i,j,nt;


/*    debug('  .. Afftex');*/
    putxy(x,y);
    if (res==1)  tab=10; else tab=6;
    dx= dx * 6;
    dy= dy * 6;
    xc= x;
    yc= y;
    xf= x+dx;
    yf= y+dy;
    p= 1;
    the_end=(ch[p]=='$');
    s="";
    while (! the_end) 
     {
      switch (ch[p]) {
                  case '@' : {
                          writeg(s,typ);
                          s="";
                          p=p+1;
                          xc=x;
                          yc=yc+6;
                          putxy(xc,yc);
                        }
                        break;
                  case ' ' : {
                          s=s+' ';
                          xc=xc+tab;
                          p=p+1;
                          if (l_motsuiv(p, ch, tab)+xc > xf) 
                             {
                               writeg(s,typ);
                               s="";
                               xc=x;
                               yc=yc+6;
                               if (yc>yf) 
                                  {
                                    do {; } while (!keypressed());
                                    i=y;
                                    do {
                                      j=x;
                                      do {
                                        putxy(j,i);
                                        writeg(" ",0);
                                        j=j+6;
                                      } while (!(j>xf));
                                      i=i+6;
                                    } while (!(i>yf));
                                    yc=y;
                                  }
                               putxy(xc,yc);
                             }
                        }
                        break;
                  case '$' : {
                          the_end= true;
                          writeg(s,typ);
                        }
                        break;
        default:
        {
          s=s+ch[p];
          p=p+1;
          xc=xc+tab;
        }
      }     /* case */
    }
  }
