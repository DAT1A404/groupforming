typedef struct person {
    char name[40];
    int personID;
    double criteria[5];
} person;

typedef struct group {
    person members[8];
    int groupNumber;
    double fitnessValue;
} group;

typedef enum command {
    seePerson;
    seeGroup;
    seeAll;
    export;
    exit;
} command;

typedef enum fileType {
    csv;
    xlsx;
} fileType;