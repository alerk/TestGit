function indent() {
    local x=$1
    # printf "indent $x:";
    if [ $x -gt 0 ]; then
        v=$(printf "%-$((4*x))s" " ");
        printf "${v}"
    fi
    # for i in {0 .. $(($x))}; do
    #     printf "\t";
    # done;
}
function generateTreeDFS(){
    dir=`echo $1 | tr -d '\r'`
    local level=`echo $2 | tr -d '\r'`
    indent $level
    echo package $dir {;
    cd $dir
    subdir=`find . -maxdepth 1 -type d | wc -l`;
    if [ $subdir -gt 1 ]; then
        for d in `ls -d */`; do
            if [ "$d" != "$1" ]; then
                dname=${d%%/*}
                generateTreeDFS $dname $((level+1));
            fi
        done
    fi
    for f in `ls -f | grep java`; do
        fname=${f%%.*}
        # echo $fname;
        # fname=${fname_with_dir##*/}
        if [[ ! -z "$fname" ]]; then
            indent $((level+1))
            echo class $fname
        fi
    done
    cd ..
    indent $level
    echo }
    echo
}
echo "@startuml"
generateTreeDFS $1 $2
echo "@enduml"