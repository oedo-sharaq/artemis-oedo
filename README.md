# artemis-oedo
artemis working directory for OEDO/SHARAQ experiments

## Installation
- Install cmake version of artemis (currently available at https://github.com/rin-yokoyama/artemis.git -b cmake).
- Set artemis environment.
```
source thisartemis.sh
```
OR
```
module load artemis
```
- Clone this repository and use cmake to build.
```
git clone https://github.com/rin-yokoyama/artemis-oedo.git
cd artemis-oedo
mkdir build
cd build
cmake ..
make install
```
- Set environment.
```
cd ..
source thisartemis-oedo.sh
```
You should be ready to use artemis with the oedo library now.
