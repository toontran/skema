import scipy.io
import os

home_dir = os.path.expanduser("~")
filepath = os.path.join(home_dir, f'data/data_2m.mtx')
A = scipy.io.mmread(filepath)

# print(type(A))
# import pdb;pdb.set_trace()

length = 1000
target_path =f'./test/data/data_{length}.mtx'
scipy.io.mmwrite(target_path, A[:length, :])
# print(f"Matrix saved in", filename)
# if len(S_exact) < 100:
#     print(S_exact)
