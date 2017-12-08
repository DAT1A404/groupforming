
/* ================= */
/* Structs and enums */
/* ================= */
typedef struct {
    char name[40];
    int personID;
    double criteria[20];
} Person;

typedef struct {
    Person members[20];
    int memberCount;
    int groupNumber;
    double fitnessValue;
} Group;

typedef struct {
    char name[40];
    double weight;
    double minimum;
} Criteria;

typedef struct {
    Person *allPersons;
    int personCount;
    Criteria *allCriteria;
    int criteriaCount;
} DataSet;

typedef struct {
    int popsize;
    int generations;
    float mutationrate;
} GASettings;

typedef struct {
    Person *persons;
    int personCount;
    Criteria *criteria;
    int criteriaCount;
    int groupCount;
} Chromosome;
