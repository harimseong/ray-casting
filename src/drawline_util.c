#include "drawline.h"

void    swap_point(t_vec2 *p0, t_vec2 *p1)
{
	t_vec2  temp;

	temp = *p0;
	*p0 = *p1;
	*p1 = temp;
}
