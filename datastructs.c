
/* ================= */
/* Structs and enums */
/* ================= */
typedef struct {
    char name[40];
    int personID;
    double criteria[10];
} person;

typedef struct {
    person members[8];
    int groupNumber;
    double fitnessValue;
} group;

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