#./build/bin/skema --input ./test/data/matrix_data_kernel_random_30_2.0.mtx --symmetric --rank 10 --window 10 --method isvd --print-level 3 --history-file ./logs/history.json --debug-file ./logs/debug --debug
#/build/bin/skema --input ./test/data/data_50.mtx --symmetric --rank 10 --window 10 --method isvd --print-level 3 --history-file ./logs/history.json --debug-file ./logs/debug --debug --kernel gaussrbf --gamma 1e1
gdb --args ./build/bin/skema --input ./test/data/data_50.mtx --symmetric --rank 10 --window 15 --method isvd --print-level 3 --history-file ./logs/history.json --debug-file ./logs/debug --debug --kernel gaussrbf --gamma 1e1 --primme_printLevel 4 
#gdb --args ./build/bin/skema --input ./test/data/data_200.mtx --symmetric --rank 10 --window 50 --method isvd --print-level 3 --history-file ./logs/history.json --debug-file ./logs/debug --debug --kernel gaussrbf --gamma 1e1 --primme_printLevel 4 


