#include "../../include/entropy.h"

void	world_show_results(const world_t *w)
{
	int	i;

	printf("\n=== SUMMARY OF GENERATED VALUES ===\n\n");
	printf("→ List of numbers greater than or equal to zero:\n");
	i = 0;
	while (w -> positives.values != NULL && i < w -> positives.length)
	{
		printf("   [%3d]  %d\n", i, w->positives.values[i]);
		i++;
	}
	if (w->positives.values == NULL)
		printf("   (empty)\n");
	printf("\n→ List of numbers less than zero:\n");
	i = 0;
	while (w->negatives.values != NULL && i < w->negatives.length)
	{
		printf("   [%3d]  %d\n", i, w->negatives.values[i]);
		i++;
	}
	if (w->negatives.values == NULL)
		printf("   (empty)\n");
	printf("\n");
}
