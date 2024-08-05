#!/bin/sh

git filter-branch -f --env-filter "GIT_AUTHOR_NAME='xyz'; GIT_AUTHOR_EMAIL='xyz@gmail.com'; GIT_COMMITTER_NAME='xyz'; GIT_COMMITTER_EMAIL='xyz@gmail.com';" HEAD