#include "sprite.h"

int compare(const void* comp1, const void* comp2)
{
	if (((t_sprite*)comp1)->distance < ((t_sprite*)comp2)->distance)
		return (1);
	return (-1);
}
