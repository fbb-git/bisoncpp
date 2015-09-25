#include "parser.ih"

    // When a block is read, process its $ and @ symbols. If it's a nested
    // block, it inherits the outer rule's stype, but it can only sensibly
    // have negative stack indices up to the number of elements of the current
    // rule. The stack starts with 0 elements, and its topmost element is
    // having the highest index value. Then, a stack element related to a rule
    // element `i' is reached using index tos - n + i, where `tos' is the
    // number of elements on the stack, `n' the number of elements in the
    // production rule, and `i' the $-index ($1, $2, $3, etc.). Assuming tos
    // is the pointer to the current stacktop, and assuming that a rule has
    // `n' elements so far, indicated as $1, $2, ... $n, followed by the
    // nested block, the stack, when the nested block's action is called, has
    // the following contents (behind the $i's the proper index relative to
    // the nested block number of elements are indicated):
    //        [higher indices in the stack]
    //
    //        tos ->  $n      [tos - n + n] = [tos + 1 - 1]
    //                ...
    //                $2
    //                $1      [tos - n + 1] = [tos + 1 - n]
    //
    //        [lower indices in the stack]
    // So, if the action called at this moment is a nested block's action,
    // then its `n' is 0, so element $n (its grammar rule's predecessor) is
    // reached as element 0: [tos - 0 - 0], element $n-1 is reached as [tos -
    // 0 - 1] etc, etc.. However, in order to make the counting more
    // intuitively, $0 is not used, but instead $-element are, like their
    // positive counterparts, counted as pure negative values. So, with hidden
    // numbers, the block-processor will add 1 to negative indices.

    // With mid-rule actions nElements is negative, counting the action block
    // as an element. A construction like
    //  rule:
    //      TOK1 TOK2
    //      {
    //          cout << $1 << ' ' << $2;
    //      }
    //      TOK3
    //
    //  is translated using a hidden block into:
    //
    //  #0001
    //      {
    //          cout << $-1 << ' ' << $0;
    //      }
    //      TOK3
    //
    //  rule:
    //      TOK1 TOK2 
    //      #0001
    //      TOK3
    //
    // Therefore, $1 becomes $-1, $2 becomes $0. The index can be computed
    // as idx + nElements + 1

int Parser::indexToOffset(int idx, int nElements) const
{
    if (idx < 0 || nElements < 0)
        ++idx;

    return nElements >= 0 ? idx - nElements : idx + nElements;
}
