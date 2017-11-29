
/* ================= */
/* Structs and enums */
/* ================= */
typedef struct {
    char name[40];
    int personID;
    double criteria[20];
} person;

typedef struct {
    person members[20];
    int memberCount;
    int groupNumber;
    double fitnessValue;
} group;

typedef struct {
    char name[40];
    double weight;
} criteria;

typedef enum {
    seePerson,
    seeGroup,
    seeAll,
    xport,
    quit
} command;

typedef enum {
    csv,
    xlsx,
    json
} fileType;

/* ================ */
/* Global variables */
/* ================ */
person *_AllPersons;
int _PersonCount;
int _GroupCount;
criteria *_Criteria;
int _CriteriaCount;