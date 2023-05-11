/* Copyright (c) 1997-1999 Miller Puckette and others.
* For information on usage and redistribution, and for a DISCLAIMER OF ALL
* WARRANTIES, see the file, "LICENSE.txt," in this distribution.  */

/* sampling */

/* customized tabwrite~ object by Orm Finnendahl February 2004*/

#include "m_pd.h"

#define SLIDE_VERSION          "0.1"

/* ------------------------- slide~ -------------------------- */

static t_class *slide_tilde_class;

typedef struct _slide_tilde
{
    t_object x_obj;
    float x_min;
    float x_max;
    t_outlet *x_minout;
    t_outlet *x_maxout;

    float x_f;
} t_slide_tilde;

static void *slide_tilde_new(void)
{
    t_slide_tilde *x = (t_slide_tilde *)pd_new(slide_tilde_class);
    x->x_minout = outlet_new(&x->x_obj, &s_float);
    x->x_maxout = outlet_new(&x->x_obj, &s_float);
    x->x_min = 0;
    x->x_max = 0;
    return (x);
}

static t_int *slide_tilde_perform(t_int *w)
{
    t_slide_tilde *x = (t_slide_tilde *)(w[1]);
    t_float *in = (t_float *)(w[2]);
    int n = (int) w[3];
    while (n--) {
      if (*in < x->x_min)
	x->x_min =  *in;
      if (*in > x->x_max)
	  x->x_max = *in;
      in++;
    }
    return (w+4);
}

static void slide_tilde_dsp(t_slide_tilde *x, t_signal **sp)
{
  dsp_add(slide_tilde_perform, 3, x, sp[0]->s_vec, sp[0]->s_n);
}

static void slide_tilde_bang(t_slide_tilde *x)
{
  if (x->x_max > -10000)
    outlet_float(x->x_maxout, x->x_max);
  if (x->x_min < 10000)
    outlet_float(x->x_minout, x->x_min);
		 x->x_min = 10000;
		 x->x_max = -10000;
}

void slide_tilde_setup(void)
{
    slide_tilde_class = class_new(gensym("slide~"), slide_tilde_new, 0,
    	sizeof(t_slide_tilde), 0, 0);
    CLASS_MAINSIGNALIN(slide_tilde_class, t_slide_tilde, x_f);
    class_addmethod(slide_tilde_class, (t_method)slide_tilde_dsp,
    	gensym("dsp"), 0);
    class_addbang(slide_tilde_class, slide_tilde_bang);
}
