#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void export_plain(group *grps, int _GroupCount);
void export_to_csv (group *groups, int groupCount);
int find_max_members(group *groups, int groupCount);
void make_header(int groupCount, FILE *fp);
void print_members(group *groups, int groupCount, int max_members, FILE *fp);
