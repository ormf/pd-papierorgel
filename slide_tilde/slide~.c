/* Copyright (c) 1997-1999 Miller Puckette and others.
* For information on usage and redistribution, and for a DISCLAIMER OF ALL
* WARRANTIES, see the file, "LICENSE.txt," in this distribution.  */

/* sampling */

/* slide~ from Max/MSP, implemented May 2023 by Orm Finnendahl*/

#include "m_pd.h"

#define SLIDE_VERSION          "0.1"

/* ------------------------- slide~ -------------------------- */

static t_class *slide_tilde_class;

typedef struct _slide_tilde
{
  t_object x_obj;
  t_float x_slide_down;
  t_float x_slide_up;
  t_outlet *x_slideout;
  t_sample x_last_y;
  t_float x_f;
} t_slide_tilde;

static void *slide_tilde_new(t_floatarg up, t_floatarg down)
{
    t_slide_tilde *x = (t_slide_tilde *)pd_new(slide_tilde_class);
    x->x_slide_up = (up == 0.0)?1:up;
    x->x_slide_down = (down == 0.0)?1:down;
    /* x->x_slideout = outlet_new(&x->x_obj, &s_float); */
    outlet_new(&x->x_obj, gensym("signal"));
    floatinlet_new(&x->x_obj, &x->x_slide_up);
    floatinlet_new(&x->x_obj, &x->x_slide_down);
    /* post("slide-up: %f",     x->x_slide_up); */
    /* post("slide-down: %f",     x->x_slide_down); */
    return (x);
}

static t_int *slide_tilde_perform(t_int *w)
{
    t_slide_tilde *x = (t_slide_tilde *)(w[1]);
    t_float *in = (t_float *)(w[2]);
    t_float *out = (t_float *)(w[3]);
    int n = (int) w[4];
    while (n--) {
      t_sample f = *in++;
      if (f < x->x_last_y) {
        *out = x->x_last_y + ((f - x->x_last_y)/x->x_slide_down);
      } else {
        if (f > x->x_last_y) {
          *out = x->x_last_y + ((f - x->x_last_y)/x->x_slide_up); }
        else *out = f;
      }
      x->x_last_y = *out;
      out++;
    }
    return (w+5);
}

static void slide_tilde_dsp(t_slide_tilde *x, t_signal **sp)
{
    dsp_add(slide_tilde_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, (t_int)sp[0]->s_n);
}

static void slide_tilde_info(t_slide_tilde *x)
{
  post("slide-down: %f",     x->x_slide_down);
  post("slide-up: %f",     x->x_slide_up);
}


static void slide_tilde_float(t_slide_tilde *x, t_float f)
{
  x->x_last_y = (t_sample) f;
}

static void slide_tilde_up(t_slide_tilde *x, t_float f)
{
  x->x_slide_up = (f == 0.0)?1:f;
}

static void slide_tilde_down(t_slide_tilde *x, t_float f)
{
  x->x_slide_down = (f == 0.0)?1:f;
}


static void slide_tilde_reset(t_slide_tilde *x)
{
  x->x_last_y = (t_sample) 0;
}



void slide_tilde_setup(void)
{
    slide_tilde_class = class_new(gensym("slide~"), slide_tilde_new, 0,
                                  sizeof(t_slide_tilde), 0, A_DEFFLOAT, A_DEFFLOAT, 0);
    CLASS_MAINSIGNALIN(slide_tilde_class, t_slide_tilde, x_f);
    class_addmethod(slide_tilde_class, (t_method)slide_tilde_dsp, gensym("dsp"), A_CANT, 0);
    class_addfloat(slide_tilde_class, slide_tilde_float);
    class_addmethod(slide_tilde_class, (t_method)slide_tilde_up, gensym("slide_up"), A_FLOAT, 0);
    class_addmethod(slide_tilde_class, (t_method)slide_tilde_down, gensym("slide_down"), A_FLOAT, 0);
    class_addmethod(slide_tilde_class, (t_method)slide_tilde_reset, gensym("reset"), 0);
    class_addmethod(slide_tilde_class, (t_method)slide_tilde_info, gensym("info"),  0);

}
