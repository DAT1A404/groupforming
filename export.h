
void export_plain(Group *grps, int _GroupCount);
void export_to_csv (Group *groups, int groupCount);
int find_max_members(Group *groups, int groupCount);
void make_header(int groupCount, FILE *fp);
void print_members(Group *groups, int groupCount, int max_members, FILE *fp);
