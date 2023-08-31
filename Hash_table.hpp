
// an implementation of a simple hash table

class Hash_table {
    private:

    struct pair {
        int data;
        bool valid; // true if has entry, or is deleted
        bool occupied; // true only if has entry
    };
    
    pair* array; // this is the storage array for the keys
    int size;
    int load; // store the number of entries occupied

    // a simple hash function
    int hash(int x) {
        return x % size;
    }

    // adjust the size of the array 
    void enlarge() {
        size *= 2;
        pair* temp = new pair[size];
        int index = 0;
        // moving to a new array
        for (int i = 0; i < size/2; i++) {
            if (array[i].valid) {
                index = hash(array[i].data);
                temp[index].data = array[i].data;
                temp[index].valid = 1;
                temp[index].occupied = array[i].occupied;
            }
        }
        delete [] array;
        array = temp;
    }

    public:
    // constructor
    Hash_table() {
        size = 50;
        array = new pair[size];
        for (int i = 0; i < 50; i++) {
            array[i].data = 0;
            array[i].valid = 0;
            array[i].occupied = 0;
        }
    }

    // constructor with parameter (array)
    Hash_table(int* insert_list, int n) {
        size = 50;
        array = new pair[size];
        for (int i = 0; i < 50; i++) {
            array[i].data = 0;
            array[i].valid = 0;
            array[i].occupied = 0;
        }
        for (int j = 0; j < n; j++) {
            insert(insert_list[j]);
        }

    }

    ~Hash_table() {
        delete [] array;
    }

    // insert function
    bool insert(int y) {
        /* insert a value into the hash table, return true if successful
        otherwise return false
        */
        // enlarge the array if load is too high
        if (load >= size/2) enlarge();
        int position = hash(y);
        int original = position;
        // resolve conflict with linear probing
        while (array[position].occupied) {
            position += 1;
            if (position >= size) position = 0;
            if (position = original) return false;
        }
        array[position].data = y;
        array[position].valid = 1;
        array[position].occupied = 1;
        load += 1;
        return true;
    }

    int search(int y) {
        // search a value y from the has table and return its index
        // return -1 if not found
        int position = hash(y);
        while (array[position].valid) {
            if (array[position].data = y) {
                return position;
            }
            position += 1;
        }
        return -1;
    }

    bool remove(int y) {
        // find a value y from the hash table and delete it
        // return true if value deleted; false if value do not exist
        int position = search(y);
        if (position == -1) return false;
        array[position].occupied = 0;
        load -= 1;
        return true;
    }


};