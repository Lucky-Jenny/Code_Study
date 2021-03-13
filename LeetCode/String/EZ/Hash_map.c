/*
 设计一个哈希表，要求包括：
  1. add(key) 插入值
  2. contains(key) 判断是否存在值
  3. remove(key) 删除值
  
(EZ)

[URL]
https://leetcode-cn.com/problems/design-hashset/
*/

/* 以下代码仅为部分的功能函数，非完整代码 */ 

typedef struct {
    int *data;
} MyHashSet;

/** Initialize your data structure here. */
#define MAX 102400
MyHashSet* myHashSetCreate()
{
    MyHashSet *obj = (MyHashSet *)malloc(sizeof(MyHashSet));
    obj->data = (int *)malloc(sizeof(int) * MAX);
    // initial -1 becuase key might be 0.
    memset(obj->data, -1, sizeof(int) * MAX);
    return obj;
}

// get the position of k (key / -1)
int getHashAddress(int *map, int now, int k)
{
    // hash i++
    for(int i = now; i < now + 1024 && i < MAX; i++){
        if(map[i] == k)
            return i;
    }
    // hash i--
    for(int i = now; i > now - 1024 && i >= 0; i--){
        if(map[i] == k)
            return i;
    }
    return -1;
}

/* If exist, do nothing */
void myHashSetAdd(MyHashSet* obj, int key)
{
    int position = 0;

    key %= MAX;
    // check exist
    if((position = getHashAddress(obj->data, key, key)) != -1)
        return;
    // insert
    if((position = getHashAddress(obj->data, key, -1)) != -1)
        obj->data[position] = key;
}

void myHashSetRemove(MyHashSet* obj, int key)
{
    int position = 0;

    key %= MAX;
    if((position = getHashAddress(obj->data, key, key)) != -1)
        obj->data[position] = -1;
}

/** Returns true if this set contains the specified element */
bool myHashSetContains(MyHashSet* obj, int key)
{
    key %= MAX;
    if(getHashAddress(obj->data, key, key) != -1)
        return true;
    else
        return false;
}

void myHashSetFree(MyHashSet* obj) {
    free(obj->data);
    free(obj);
}

/**
 * Your MyHashSet struct will be instantiated and called as such:
 * MyHashSet* obj = myHashSetCreate();
 * myHashSetAdd(obj, key);
 
 * myHashSetRemove(obj, key);
 
 * bool param_3 = myHashSetContains(obj, key);
 
 * myHashSetFree(obj);
*/