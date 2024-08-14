chmod +x ./grep.sh
        echo "hello" | ./grep.sh -E "hello"  # Should return 0
        if [ $? -ne 0 ]; then echo "Test #0 failed"; exit 1; fi

        ./grep.sh -E "world" <<< "hello"  # Should return 1
        if [ $? -ne 1 ]; then echo "Test #1 failed"; exit 1; fi

        ./grep.sh -E "\d\d\d\d" <<< "2023"  # Should return 0
        if [ $? -ne 0 ]; then echo "Test #2 failed"; exit 1; fi

        ./grep.sh -E "\d\d\d\d" <<< "abcd"  # Should return 1
        if [ $? -ne 1 ]; then echo "Test #3 failed"; exit 1; fi

        ./grep.sh -E "[ah]" <<< "hello"  # Should return 0
        if [ $? -ne 0 ]; then echo "Test #4 failed"; exit 1; fi

        ./grep.sh -E "[^a-z]" <<< "1234"  # Should return 0
        if [ $? -ne 0 ]; then echo "Test #5 failed"; exit 1; fi

        ./grep.sh -E "^hello" <<< "hello world"  # Should return 0
        if [ $? -ne 0 ]; then echo "Test #6 failed"; exit 1; fi

        ./grep.sh -E "world$" <<< "hello world"  # Should return 0
        if [ $? -ne 0 ]; then echo "Test #7 failed"; exit 1; fi

        ./grep.sh -E "o+" <<< "hellooo"  # Should return 0
        if [ $? -ne 0 ]; then echo "Test #8 failed"; exit 1; fi

        ./grep.sh -E "colo?r" <<< "color"  # Should return 0
        if [ $? -ne 0 ]; then echo "Test #9 failed"; exit 1; fi

        ./grep.sh -E "colo?r" <<< "colour"  # Should return 1
        if [ $? -ne 1 ]; then echo "Test #10 failed"; exit 1; fi

        ./grep.sh -E "d.g" <<< "dog"  # Should return 0
        if [ $? -ne 0 ]; then echo "Test #11 failed"; exit 1; fi

        ./grep.sh -E "(cat|dog)" <<< "cat"  # Should return 0
        if [ $? -ne 0 ]; then echo "Test #12 failed"; exit 1; fi

        echo "All tests passed!"; exit 0;