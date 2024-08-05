#!/bin/bash

############# First push all changes to mater and execute this script #############

init_setup() {
	# remember credential for 1hr (3600s)
	git config credential.helper 'cache --timeout=3600'

	# locally checkout master branch
	git checkout master
}

create_branch() {

	echo "Creating branch.................................. $1"
	
	# checkout master branch first
	git checkout master
	
	# delete local branch
	git branch -d $1
		
	# delete remote branch
	git push origin --delete $1
		
	# create branch
	git checkout -b $1
	
	# delete files which are not required for this branch
	if [[ $1 == "release" ]]; then
		git rm -r appdata/datafeed/historical*
	fi
		
	# commit changes
	git commit -am "updated data"

	# push remote branch
	git push -u origin $1
	
	echo "Branch creation done.................................. $1"
	sleep 5
}

# exeucte functions
init_setup
create_branch release

# checkout master branch back
git checkout master

# undo changes
#git reset
#git checkout .

# remove untracked files
#git clean -df
