import scipy.io
import os

home_dir = os.path.expanduser("~")
filepath = os.path.join(home_dir, f'data/data_2m.mtx')
A = scipy.io.mmread(filepath)

print(type(A))
import pdb;pdb.set_trace()

# scipy.io.mmwrite(filename, A_csr)
# print(f"Matrix saved in", filename)
# if len(S_exact) < 100:
#     print(S_exact)
