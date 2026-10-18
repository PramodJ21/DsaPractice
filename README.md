# DsaPractice

A comprehensive collection of 68 Data Structures and Algorithms implementations in C covering Stacks, Queues, Singly Linked Lists, Doubly Linked Lists, and Mixed applications.

**Author:** PramodJ21

---

## Repository Structure

```
DsaPractice/
├── Stack/                  (Questions 1 – 11)
├── Queue/                  (Questions 12 – 23)
├── SinglyLinkedList/       (Questions 24 – 42)
├── DoublyLinkedList/       (Questions 43 – 58)
└── Mixed/                  (Questions 59 – 68)
```

---

## Problem Index

### 1. Stack (Questions 1 – 11)
- **1. StackUsingArray.c**: Stack using an array with `push`, `pop`, `peek`, `isEmpty`, `isFull`, and `display`.
- **2. StackUsingLL.c**: Stack using a linked list with $O(1)$ head operations.
- **3. ReverseStringUsingStack.c**: String reversal using a character stack.
- **4. BalancingParanthesis.c**: Balanced parentheses, brackets, and braces checker.
- **5. TwoStacksInOneArray.c**: Two stacks growing from opposite ends in a single array.
- **6. UndoOperation.c**: Text editor undo simulation using a stack.
- **7. BrowserHistory.c**: Browser history tracking (`visit`, `back`, `displayCurrentPage`).
- **8. PostfixEvaluation.c**: Postfix arithmetic expression evaluation.
- **9. InfixToPostfix.c**: Infix to postfix conversion respecting operator precedence and parentheses.
- **10. NextGreaterElement.c**: $O(N)$ Next greater element to the right using a monotonic stack.
- **11. StackPermutation.c**: Validating stack permutations of input sequences.

### 2. Queue (Questions 12 – 23)
- **12. QueueUsingArray.c**: Linear queue using an array (`enqueue`, `dequeue`, `front`, `isEmpty`, `isFull`, `display`).
- **13. CircularQueueArray.c**: Circular queue using an array with wraparound handling.
- **14. QueueUsingLL.c**: Queue using linked list with front and rear pointers.
- **15. QueueUsingTwoStacks.c**: Queue using two stacks with amortized $O(1)$ operations.
- **16. DequeArray.c**: Double-ended queue (deque) on a circular array.
- **17. PrinterQueue.c**: Print job spooler processing jobs in FIFO order.
- **18. TicketCounter.c**: Ticket counter line serving arriving customers.
- **19. RoundRobinScheduling.c**: Round-robin CPU scheduler using a circular queue.
- **20. QueueReversal.c**: Queue reversal using an auxiliary stack.
- **21. FirstNonRepeatingChar.c**: First non-repeating character in a stream.
- **22. InterleaveQueue.c**: Interleaving the first and second halves of a queue using a stack.
- **23. JosephusProblem.c**: Josephus elimination circle simulation using a circular queue.

### 3. Singly Linked List (Questions 24 – 42)
- **24. SLLOperations.c**: Basic SLL operations (`insertAtBeginning`, `insertAtEnd`, `deleteFromBeginning`, `deleteFromEnd`, `display`).
- **25. InsertAtPosition.c**: 1-based index node insertion with boundary handling.
- **26. DeleteAtPosition.c**: 1-based index node deletion handling empty, single, and boundary cases.
- **27. SearchElement.c**: Search for a value and return 1-based position of first occurrence.
- **28. CountSumAverage.c**: Node count, sum, and average of values.
- **29. ReverseSinglyLinkedList.c**: In-place pointer reversal ($O(1)$ space).
- **30. MiddleNode.c**: Slow and fast pointer technique (Tortoise and Hare).
- **31. KthFromEnd.c**: Finding $k$-th node from end in a single traversal.
- **32. RemoveDuplicates.c**: Duplicate removal from unsorted list preserving order.
- **33. ConcatenateLists.c**: In-place concatenation of two linked lists without node creation.
- **34. MusicPlaylistSLL.c**: Music playlist manager (`addSong`, `removeSong`, `searchSong`, `displayPlaylist`).
- **35. StudentRecordManagement.c**: Student database storing roll numbers and marks.
- **36. PolynomialRepresentation.c**: Polynomial representation sorted in descending order of exponents.
- **37. PolynomialAddition.c**: Polynomial addition combining matching degree terms.
- **38. SortedInsertSLL.c**: Insertion into a sorted list preserving ascending order.
- **39. SplitList.c**: Splitting list into two equal halves using slow/fast pointers.
- **40. CycleDetection.c**: Floyd's cycle detection algorithm and cycle entry detection.
- **41. MergeSortedLists.c**: In-place merge of two sorted linked lists.
- **42. DeleteByValue.c**: Deleting all occurrences of a specified value across head, middle, and tail.

### 4. Doubly Linked List (Questions 43 – 58)
- **43. DLLOperations.c**: DLL insertion and deletion at beginning and end.
- **44. InsertAtPositionDLL.c**: Inserting a node at a specified 1-based position.
- **45. DeleteAtPositionDLL.c**: Deleting a node at a specified position updating both neighbors.
- **46. DisplayBothDirectionsDLL.c**: Bidirectional display (head-to-tail and tail-to-head).
- **47. SearchAndUpdateDLL.c**: Search for value and update node value at position.
- **48. ReverseDLL.c**: Reversing DLL by swapping `prev` and `next` pointers.
- **49. DeleteAllNodesDLL.c**: Freeing all nodes and resetting head/tail pointers.
- **50. FindPrevNextDLL.c**: `findPrev(x)` and `findNext(x)` predecessor/successor queries.
- **51. BrowserNavigationDLL.c**: Browser history with `visit`, `back`, and `forward`.
- **52. MusicPlayerDLL.c**: Non-circular playlist with boundary protection.
- **53. TrainCoachManagement.c**: Train coach management with bidirectional display.
- **54. LRUCacheSimulation.c**: Least-Recently-Used (LRU) Cache using a DLL and hash map.
- **55. PalindromeCheckDLL.c**: Palindrome check comparing inward from head and tail.
- **56. SortedInsertDLL.c**: Sorted insertion into a DLL.
- **57. DeleteGivenNodeDLL.c**: Direct $O(1)$ deletion of a given node pointer.
- **58. CircularDoublyLinkedList.c**: Complete circular DLL with invariant maintenance.

### 5. Mixed Questions (Questions 59 – 68)
- **59. StackUsingTwoQueues.c**: Stack implemented with two queues.
- **60. QueueWithReverseDisplay.c**: Queue using linked list with recursive non-destructive reverse display.
- **61. PalindromeLinkedListUsingStack.c**: Palindrome verification of linked list using a stack.
- **62. CircularQueueUsingLL.c**: Circular queue implemented using a circular linked list with single `rear` pointer.
- **63. QueueSimulationUnderflow.c**: Trace of enqueue/dequeue sequence with underflow tracking.
- **64. VIPQueueSimulation.c**: Dual-priority customer service queue (VIP served before Regular).
- **65. StackTraceOperations.c**: Step-by-step stack visualization and underflow detection.
- **66. DequeUsingDLL.c**: Deque using a doubly linked list with $O(1)$ operations at both ends.
- **67. LinkedListPointerTrace.c**: Memory address and pointer mutation tracer for head/tail operations.
- **68. StackQueueArrayVsLLComparison.c**: Architectural comparison of array vs linked-list implementations demonstrating static overflow vs dynamic heap allocations.

---

## Compilation & Execution

To compile any file:
```bash
gcc -Wall -Wextra <filename>.c -o <output_binary> -lm
./<output_binary>
```

To compile and run all programs in a folder:
```bash
for f in *.c; do gcc -Wall -Wextra "$f" -lm && ./a.out && rm ./a.out; done
```
