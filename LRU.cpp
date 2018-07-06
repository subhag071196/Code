 
struct node
{
    int val;
    int key;
    node* prev;
    node* next;
};

unordered_map<int,pair<int,node*> > mp;   //p.first = value, p.second = node in list.
int used;
int maxcap;

node* tail;
node* head;

LRUCache::LRUCache(int capacity) 
{
    used = 0;
    maxcap = capacity;
    mp.clear();
    head = new node();
    tail = new node();
    head->key = INT_MAX;
    head->val = INT_MAX;
    head->next = tail;
    head->prev = NULL;
    tail->key = INT_MIN;
    tail->val = INT_MIN;
    tail->prev = head;
    tail->next = NULL;
}

int LRUCache::get(int key) 
{
    if(mp.find(key) == mp.end()) return -1;
    else
    {
        node* tmp = mp[key].second;
        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;
        tmp->next = head->next;
        head->next = tmp;
        tmp->prev = head;
        tmp->next->prev = tmp;
        return tmp->val;
    }
}

void LRUCache::set(int key, int value) 
{
    if(mp.find(key) != mp.end())
    {
        node* tmp = mp[key].second;
        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;
        tmp->val = value;
        tmp->next = head->next;
        head->next = tmp;
        tmp->next->prev = tmp;
        tmp->prev = head;
    }
    else 
    {
        node* tmp = new node();
        tmp->key = key;
        tmp->val = value;
        tmp->next = head->next;
        tmp->next->prev = tmp;
        head->next = tmp;
        tmp->prev = head;
        mp[key] = {value,tmp};
        used++;
        if(used > maxcap)
        {
            node* lru = tail->prev;
            lru->prev->next = tail;
            tail->prev = lru->prev;
            mp.erase(lru->key);
            delete(lru);
            used--;
        }
    }
}
