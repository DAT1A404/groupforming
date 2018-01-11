
#define NAME_MAX_LENGTH 40
#define MEMBER_MAX_COUNT 20
#define CRITERIA_MAX_COUNT 20

/* ================= */
/*       Structs     */
/* ================= */
typedef struct {
    char name[NAME_MAX_LENGTH];
    int personID;
    double criteria[CRITERIA_MAX_COUNT];
} Person;

typedef struct {
    Person members[MEMBER_MAX_COUNT];
    int memberCount;
    int groupNumber;
    double fitnessValue;
} Group;

typedef struct {
    char name[NAME_MAX_LENGTH];
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
    int fitnessChecked;
    double fitness;
} Chromosome;
