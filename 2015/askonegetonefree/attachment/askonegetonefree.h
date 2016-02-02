#ifndef ASKONEGETONEFREE_H
#define ASKONEGETONEFREE_H

struct AnswerTag;
typedef struct AnswerTag{
	int p,q;
} Answer;
Answer query(int r);
Answer guess(int N);

#endif
