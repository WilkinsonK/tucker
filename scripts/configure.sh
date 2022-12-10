# Wrapper script around cmake to make-ready this
# project as intended.

if [[ $(basename $SHELL) = 'zsh' ]]; then
    emulate bash
fi

# Compares two version numbers to determine if
# they are equal to, greater than or less than.
# Snagged from: https://stackoverflow.com/questions/4023830/how-to-compare-two-strings-in-dot-separated-version-format-in-bash
vercomp () {
    if [[ $1 == $2 ]]
    then
        return 0
    fi
    local IFS=.
    local i ver1=($1) ver2=($2)
    # fill empty fields in ver1 with zeros
    for ((i=${#ver1[@]}; i<${#ver2[@]}; i++))
    do
        ver1[i]=0
    done
    for ((i=0; i<${#ver1[@]}; i++))
    do
        if [[ -z ${ver2[i]} ]]
        then
            # fill empty fields in ver2 with zeros
            ver2[i]=0
        fi
        if ((10#${ver1[i]} > 10#${ver2[i]}))
        then
            return 1
        fi
        if ((10#${ver1[i]} < 10#${ver2[i]}))
        then
            return 2
        fi
    done
    return 0
}

if [[ ! $(which cmake) ]]; then
    echo "error: cmake is not installed. exiting."
    exit 1
fi

vercomp $(cmake --version | cut -d' ' -f3 | head -n1) '3.25.0'
if [[ $? = 2 ]]; then
    echo "error: using incompatible cmake install. expected >=3.25.0"
    exit 1
fi

cmake -Bdist .
