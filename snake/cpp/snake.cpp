#include "snake.h"
#include <vector>

std::vector<snake_segment_st> snake_init(int size_snake)
{
std::vector<snake_segment_st> segments;
snake_segment_st seg;

{
int i;
for (i=0; i<size_snake; i++)
seg.x = i;
segments.push_back(seg);
}
return segments;
}