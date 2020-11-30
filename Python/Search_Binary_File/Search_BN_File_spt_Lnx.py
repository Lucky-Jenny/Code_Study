#coding=utf-8
#Python3默认不兼容magic，所以这个方法需要重装magic
#参考网址(找了老半天....)：https://blog.csdn.net/qq_33472146/article/details/94720551
import magic
import io
import os
import re
import codecs
import time

_TEXT_BOMS = (
    codecs.BOM_UTF16_BE,
    codecs.BOM_UTF16_LE,
    codecs.BOM_UTF32_BE,
    codecs.BOM_UTF32_LE,
    codecs.BOM_UTF8,
)

# 获取当前路径
pwd = os.getcwd()

# 要搜索的文件夹路径
file_path = "/home/LX/Git/Code_Study/"

# 二进制文件/总文件个数 初始化
Cnt_BN_File = 0
Cnt_File = 0

# 把结果输出到某个文件中（用时间后缀来保持文件的唯一性）
BN_List_File = pwd + "/Result/BN_list-" + time.strftime("%m-%d-%H%M") + ".txt"

def is_binary_file_1(ff):
    '''
    根据text文件数据类型判断是否是二进制文件
    :param ff: 文件名（含路径）
    :return: True或False，返回是否是二进制文件
    '''
    with open(ff, 'rb') as file:
        initial_bytes = file.read(8192)
        file.close()
        for bom in _TEXT_BOMS:
            if initial_bytes.startswith(bom):
                continue
            else:
                if b'\0' in initial_bytes:
                    #print(True)
                    return True
    #(False)
    return False

def is_binary_file_2(ff):
    '''
    根据magic文件的魔术判断是否是二进制文件
    :param ff: 文件名（含路径）
    :return: True或False，返回是否是二进制文件
    '''
    mime_kw = 'x-executable|x-sharedlib|octet-stream|x-object'  ###可执行文件、链接库、动态流、对象
    try:
        magic_mime = magic.from_file(ff, mime=True)
        magic_hit = re.search(mime_kw, magic_mime, re.I)
        if magic_hit:
            #print(True)
            return True
        else:
            #print(False)
            return False
    except Exception as e:
        return False

def Add_File(str_path):
    '''
    a+追加方式对文件进行写操作
    若文件不存在，自动创建
    '''
    sp = str_path + '\n'
    fp = io.open(BN_List_File, "a+", encoding="utf-8")
    fp.write(sp)
    fp.close()

# 递归遍历path，同时找出Binary
def Recursive_Traversal_BN(path):
    '''
    这个地方必须要声明global，意思是全局变量
    否则会默认为局部变量，语法上会出错
    '''
    global Cnt_BN_File
    global Cnt_File

    parents = os.listdir(path)
    for parent in parents:
        child = os.path.join(path,parent)
        #print(child)
        if os.path.isdir(child):
            '''这里用了个递归的方法'''
            Recursive_Traversal_BN(child)
        else:
            Cnt_File += 1
            print(child)
            if(any((is_binary_file_1(child), is_binary_file_2(child)))):
                Add_File(child)
                print(True)
                Cnt_BN_File += 1

'''
# 也是遍历文件，该方法利用os.walk的特性直接区分了文件夹和文件
def walkFile(dd):
    for root, dirs, files in os.walk(dd):

        # root 表示当前正在访问的文件夹路径
        # dirs 表示该文件夹下的子目录名list
        # files 表示该文件夹下的文件list

        # 遍历文件
        for f in files:
            print(is_binary_file_1(os.path.join(root, f)))

        # 遍历所有的文件夹
        for d in dirs:
            print(os.path.join(root, d))
'''


if __name__ == "__main__":
    Add_File("【二进制文件路径】")
    Recursive_Traversal_BN(file_path)
    Add_File(("【总数统计】\n二进制个数：{0}  文件总数：{1}").format(Cnt_BN_File, Cnt_File))
    # {:.3%} 用百分比表示，小数点后保留3位
    Add_File(("结果比例：{:.3%}").format(Cnt_BN_File/Cnt_File))
    print(("二进制个数：{0}  文件总数：{1}").format(Cnt_BN_File, Cnt_File))
