#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    float x, y;
} Point;

float dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

typedef struct {
    float x, y, z;
} link_t;

bool is_null(link_t **link)
{
    return !*link;
}

int main() {
    // Point A = {0, 0};
    // Point B = {4, 0};
    // Point C = {2, 4};
    // Point P = {5, 5};

    // Point AB = {B.x - A.x, B.y - A.y};
    // Point BC = {C.x - B.x, C.y - B.y};
    // Point CA = {A.x - C.x, A.y - C.y};
    // Point AP = {P.x - A.x, P.y - A.y};
    // Point BP = {P.x - B.x, P.y - B.y};
    // Point CP = {P.x - C.x, P.y - C.y};

    // int dotABAP = dot(AB, AP);
    // int dotBCBP = dot(BC, BP);
    // int dotCACP = dot(CA, CP);

    // if (dotABAP > 0 && dotBCBP > 0 && dotCACP > 0 ||
    //     dotABAP < 0 && dotBCBP < 0 && dotCACP < 0) {
    //     printf("Point P is inside the triangle ABC\n");
    // } else {
    //     printf("Point P is outside the triangle ABC\n");
    // }
    // link_t *link = malloc(sizeof(link_t));
    link_t *link = NULL;
    printf("%d\n", is_null(&link));
    // free(link);

    return 0;
}
