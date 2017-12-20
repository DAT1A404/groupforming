# groupforming-project
This program strives towards efficiently generating approximately optimal groups from a given dataset through a genetic algorithm with the utilisation of a fitness-function.
A group of six first-year students at AAU, studying CS, has worked on this project through a period of two months.

## usage
Compile program through makefile. Simply run `make` and `make clean` to remove executable and `.o`-files.

Execute program with `groupforming.exe` or `./groupforming` depending on your platform. If you wish to set the debug flag at launch time, parse the ` -v` argument at execution.

The program will prompt the user at each stage that user-intervention is needed with contextual instruction.
## example datasets
`data-belbin.txt` contains a small dataset with Belbins team-roles for testing multiple criteria

`data-five-men.txt` contains a dataset with multiple criteria and few women to test algorithms efficacy with minimum-criteria defined

`data-five.txt` contains a dataset with multiple criteria, different weights and evenly distributed properties on dataset members

`datsw.txt` contains representative dataset of program use-case at AAU for computer science and software engineering with relevant data and criteria, according to previous project analysis
