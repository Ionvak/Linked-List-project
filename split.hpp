#include "sequence.hpp"

#ifndef SPLIT
#define SPLIT

template <typename Key, typename Info>
void split_pos(Sequence<Key, Info>& seq, int start_pos,int len1, int len2, int count,Sequence <Key,Info>& seq1, Sequence<Key, Info>& seq2){
    typename Sequence<Key,Info>::Iterator temp1 = seq.GetFirst();
    typename Sequence<Key,Info>::Iterator temp2 = seq.GetFirst();
    seq1.Clear();
    seq2.Clear();
    int i = 0;
    while(temp1 != nullptr && i++ < start_pos) temp1++;

    i=0;
    while(i++ < count){
        for(int n=0; temp1 != nullptr && n<len1 ;n++){
            seq1.PushFront((*temp1).value, (*temp1).ID);
            temp2 = temp1;
            temp1++;
            seq.Remove(temp2);
            temp2 = nullptr;
        }

        for(int m=0; temp1 != nullptr && m<len2 ;m++){
            seq2.PushFront((*temp1).value, (*temp1).ID);
            temp2 = temp1;
            temp1++;
            seq.Remove(temp2);
            temp2 = nullptr;
        }

        if(temp1 == nullptr) break;
    }
}

template <typename Info, typename Key>
void split_key(Sequence<Info,Key>& seq, const Key& start_key, int start_occ, int len1, int len2, int count, Sequence <Info,Key>& seq1, Sequence<Info,Key>& seq2){
    typename Sequence<Info,Key>::Iterator temp = seq.GetFirst();
    int i=0, pos=0;

    while(temp != nullptr && i<start_occ){
        if((*temp).ID == start_key) i++;
        if(i == start_occ) break;
        temp++;
        pos++;
    }

    if(temp != nullptr && start_occ > 0) split_pos(seq,pos,len1,len2,count,seq1,seq2);
}


#endif // SPLIT
