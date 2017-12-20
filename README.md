# groupforming-project
This program stives towards efficiently generating approximately optimal groups from a given dataset through a genetic algorithm with the utilisation of a fitness-function.

## usage
Compile program through makefile. Simply run `make` and `make clean` to remove executable and `.o`-files.

Execute program with `groupforming.exe` or `./groupforming` depending on your platform. If you wish to set the debug flag at launch time, parse the ` -v` argument at execution.

The program will prompt the user at each stage that user-intervention is needed with contextual instruction.
## example datasets
`data-belbin.txt`
contains small dataset with Belbins team-roles for testing

`data-five-men.txt`
contains dataset with multiple criteria and few women to test minimum-criteria in edge cases

`data-five.txt`
contains dataset with multiple criteria, different weights and evenly distributed members

`datsw.txt`
contains representative dataset of use-case at AAU for computer science with relevant data and criteria
