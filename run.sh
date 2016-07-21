/home/sayuri/bin/clion-1.0.4/bin/cmake/bin/cmake \
    --build /home/sayuri/.clion10/system/cmake/generated/8eaf02d3/8eaf02d3/Debug \
    --target main_webpp \
    -- \
    -j 8 \
&& \
spawn-fcgi -p 8000 \
    -n /home/sayuri/.clion10/system/cmake/generated/8eaf02d3/8eaf02d3/Debug/main_webpp
