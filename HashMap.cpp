#include "HashMap.hpp"
#include <iostream>

namespace
{
    unsigned int default_hasher(const std::string& text)
    {
        unsigned int A = 7919;
        unsigned int B = 13331;
        unsigned int C = 929;
        unsigned int hash = 29;

        for (int i = 0; i < text.length(); ++i)
        {
            hash += (hash * A) ^ (text[i] * B);
        }

        return hash % C;
    }
}

HashMap::HashMap()
    : hasher{default_hasher}, max_buckets{HashMap::initialBucketCount}, bucket_size{0}, bucket_array{new Node*[max_buckets]}
{
    create_bucket(bucket_array, max_buckets);
}

HashMap::HashMap(HashFunction initial_hasher)
    : hasher{initial_hasher}, max_buckets{HashMap::initialBucketCount}, bucket_size{0}, bucket_array{new Node*[max_buckets]}
{
    create_bucket(bucket_array, max_buckets);
}

HashMap::HashMap(const HashMap& hm)
    : hasher{hm.hasher}, max_buckets{hm.max_buckets}, bucket_size{hm.bucket_size}, bucket_array{new Node*[hm.max_buckets]}
{
    create_bucket(bucket_array, max_buckets);
    copy_bucket(bucket_array, hm.bucket_array, hm.bucket_size);
}

HashMap::~HashMap()
{
    for (int i = 0; i < max_buckets; ++i)
    {
        while (bucket_array[i] != nullptr)
        {   
            Node* temp_node = bucket_array[i];
            bucket_array[i] = bucket_array[i]->next;
            delete temp_node;
        }
    }
    delete[] bucket_array;
}

HashMap& HashMap::operator=(const HashMap& hm)
{
    if (this != &hm)
    {
        Node** new_bucket_array = new Node*[hm.max_buckets];
        create_bucket(new_bucket_array, hm.max_buckets);
        copy_bucket(new_bucket_array, hm.bucket_array, hm.max_buckets);

        bucket_size = hm.bucket_size;
        max_buckets = hm.max_buckets;
        hasher = hm.hasher;

        this->~HashMap();
        bucket_array = new_bucket_array;
    }
    return *this;
}

void HashMap::add(const std::string& key, const std::string& value)
{
    if ((double)((bucket_size + 1) / max_buckets) > 0.8)
    {
        unsigned int new_max_bucket = max_buckets * 2 + 1;
        Node** new_bucket_array = new Node*[new_max_bucket];
        
        create_bucket(new_bucket_array, new_max_bucket);

        for (int i = 0; i < max_buckets; ++i)
        {
            Node* next_node = bucket_array[i];
            while(next_node != nullptr)
            {
                unsigned int new_index = hasher(next_node->key) % new_max_bucket;
                add_to_bucket(next_node->key, next_node->value, new_bucket_array[new_index]);
                next_node = next_node->next;
            }
        }
        this->~HashMap();
        max_buckets = new_max_bucket;
        bucket_array = new_bucket_array;
    }
    unsigned int hashed_index = hasher(key) % max_buckets;
    add_to_bucket(key, value, bucket_array[hashed_index]);

    bucket_size++;
}

void HashMap::remove(const std::string& key) 
{
    if (contains(key))
    {
        unsigned int hashed_index = hasher(key) % max_buckets;
        Node* temp_node;

        if (bucket_array[hashed_index]->key == key)
        {
            temp_node = bucket_array[hashed_index]->next;
            delete bucket_array[hashed_index];
            bucket_array[hashed_index] = temp_node;
            bucket_size--;
        }
        else
        {
            while (bucket_array[hashed_index] != nullptr && bucket_array[hashed_index]->next != nullptr)
            {
                if (bucket_array[hashed_index]->next->key == key)
                {
                    temp_node = bucket_array[hashed_index]->next->next;
                    delete bucket_array[hashed_index]->next;
                    bucket_array[hashed_index] = temp_node;

                    bucket_size--;
                    break;
                }
                else
                {
                    bucket_array[hashed_index] = bucket_array[hashed_index]->next;
                }
            }
        }
    }
}

bool HashMap::contains(const std::string& key) const
{
    if (value(key) == "")
    {
        return false;
    } 
    unsigned int index = hasher(key) % max_buckets;
    Node* next_pointer = bucket_array[index];

    while(next_pointer != nullptr)
    {
        if (next_pointer->key == key)
        {
            return true;
        }
        next_pointer = next_pointer->next; 
    } 
    return false;
}

std::string HashMap::value(const std::string& key) const
{
    unsigned int index = hasher(key) % max_buckets;
    Node* next_pointer = bucket_array[index];

    while(next_pointer != nullptr)
    {
        if (next_pointer->key == key)
        {
            return next_pointer->value;
        }
        next_pointer = next_pointer->next;
    }
    return "";
}

unsigned int HashMap::size() const
{
    return bucket_size;
}

unsigned int HashMap::bucketCount() const
{
    return max_buckets;
}

double HashMap::loadFactor() const
{
    return (double) bucket_size / max_buckets;
}

unsigned int HashMap::maxBucketSize() const
{ 
    unsigned int max_size = 0;
    unsigned int size_counter;

    for (int i = 0; i < max_buckets; ++i)
    {
        size_counter = 0;
        Node* next_pointer = bucket_array[i];
        while (next_pointer != nullptr)
        {   
            size_counter += 1;
            next_pointer = next_pointer->next;
        }
        if (size_counter > max_size)
        {
            max_size = size_counter;
        }
        
    }
    return max_size;
}

void HashMap::clear_all()
{
    for (int i = 0; i < max_buckets; ++i)
    {
        Node* first_pointer = bucket_array[i];

        while(first_pointer != nullptr)
        {
            Node* temp_node = first_pointer;
            first_pointer = first_pointer->next;
            delete temp_node;
        }
        bucket_array[i] = nullptr;
    } 
    /*this->~HashMap();
    Node** bucket_array = new Node*[max_buckets];
    create_bucket(bucket_array, max_buckets); */
    bucket_size = 0;

} 




// PRIVATE FUNCTIONS


void HashMap::create_bucket(Node** &b_array, const unsigned int& a_size)
{
    for (int i = 0; i < a_size; ++i)
    {
        b_array[i] = nullptr;
    }
}

void HashMap::copy_bucket(Node** target, Node** const &source, const unsigned int& a_size)
{
    for (int i = 0; i < a_size; ++i)
    {
        Node* source_pointer = source[i];

        if (source_pointer != nullptr)
        {
            Node* target_pointer = new Node{target[i]->key, target[i]->value, target[i]->next};

            while(source_pointer != nullptr)
            {
                target_pointer->key = source_pointer->key;
                target_pointer->value = source_pointer->value;

                source_pointer = source_pointer->next;

                if (source_pointer == nullptr)
                {
                    target_pointer->next = nullptr;
                }
                else
                {
                    target_pointer->next = new Node;
                    target_pointer = target_pointer->next;
                }
            }
        }
    } 
}

void HashMap::add_to_bucket(const std::string& key, const std::string& value, Node* &current_pointer)
{
    Node* bucket_pointer = new Node{key, value, nullptr};

    if (current_pointer == nullptr)
    {
        current_pointer = bucket_pointer;
    }
    else if (current_pointer->next == nullptr)
    {
        current_pointer->next = bucket_pointer;
    }
    else
    {
        while (current_pointer->next != nullptr)
        {
            current_pointer = current_pointer->next;
        }
        current_pointer->next = bucket_pointer;
    }
}

