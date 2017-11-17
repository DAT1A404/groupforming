typedef struct person{
    char name[40];
    int personID;
    double criteria[5];
}person;

typedef struct group{
    person;
    int groupNumber;
    double fitnessValue;
}group;
