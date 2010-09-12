FILE=/tmp/revisions.txt
# search git log for all the commits
git log | grep -E ^commit > $FILE
# count lines
wc -l $FILE
# remove temp file
rm $FILE
