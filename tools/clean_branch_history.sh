#!/bin/sh

git config credential.helper 'cache --timeout=600'

OLD_BRANCH=$1

# Checkout to a temporary branch:
git checkout --orphan TEMP_BRANCH

# Add all the files:
git add .

# Commit the changes:
git commit -am "Initial commit"

# Delete the old branch:
git branch -D $OLD_BRANCH

# Rename the temporary branch to master:
git branch -m $OLD_BRANCH

# Finally, force update to our repository:
#git push -f origin $OLD_BRANCH

