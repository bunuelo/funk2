\newcommand{\gen}{\preceq_{G}}

**Rev.** 0.  **Released:**  Wednesday, April 29 2009.  **Due:** Wednesday, Mar 18 2009, 7:00pm.


## Goals

Our goal with this lab is to make you familiar and confident with using tools from different sub-fields in artificial intelligence so that you can think concretely about how they should work together in an autonomous problem solving agent.

In this first laboratory, you will learn about ways to represent, learn and use knowledge to solve problems.   We will present the problems within complete problem solving frameworks, beginning with the very simplest.

# Problem 1 (Ch 1)

In some situations emotions can be useful ways of thinking, while in others
these same ways of thinking can be detrimental.  For example, if one sees
their child walking near a cliff, becoming Anxious is a very relevant
response that hones the senses and primes fast motor reactions.  However,
in the context of taking a test, some people feel Test Anxiety, a related
mental state, where these same effects make it difficult for complex ways of
thinking to operate without being distracted by these same "fight or
flight" reactions.

 **a)** Pick three emotions and describe their characteristics, as turning on
    or off resources.

 **b)** Using these same emotions, describe situations where these emotions
    and their characteristics would be helpful.  Describe situations where
    these characteristics would be detrimental.


# Problem 2 (Ch 2)

Regarding Remembering, Minsky explains that "On the surface, it might seem
easy enough--like dropping a note into a box and then taking it out when
you need it.  But when we look more closely, we see that this must involve
many processes: you first must decide what items your note should contain,
and find suitable ways to represent them--and then you must make some
connections to them so that after you store those parts away, you'll be
able to reassemble them."

What are examples of the types of items your note should contain?
For example, you might need to later recall prerequisites for a
successful action toward a goal.  Try to think of three types
of knowledge related to mental events as well as three related to external
events.

# Problem 3 (Ch 3)

Minsky: "What makes feelings so hard to describe? Is this because feelings are
so simple and basic that there's nothing more to be said about them?  No, its 
precisely the opposite, because...what we call feelings are the results of 
attempts (by some parts of one's mind) to describe entire mental conditions.
However, every mental state is so complex that any brief description of it 
could capture just a few aspects of it." (Ch 3)

 **a)** How does this imply a limitation on our introspective abilities?

 **b)** How does this relate to using abstract or ambiguous terminology (\eg "suitcase words")?


# Problem 4 (Ch 3)

In 3-8, Minsky discusses emotional exploitation as a method of self-control.
Describe some memories you could conjure to indirectly cause reactions and 
resolve one of these goal conflicts. 

 **example)** You want to study for a test, and you are tired.  
   Conjure a memory of failing the test to elicit a Fearful state, or
   Imagine a competition between another colleague to obtain Anger.

 **a)** You are on a diet, and want to eat Double Fudge ice cream.

 **b)** You want a good grade, and you are bored in class.

 **c)** You want to yell at a police officer, and not be arrested.


# Problem 5 (Ch 4)

Regarding the word Consciousness, Minsky states, "I'll argue that it would
be a mistake to believe in any such entity--because we ought to be asking
this question, instead: "Isn't it remarkable that any single word or phrase
could have come to mean so many different things?"

Think of when the term "consciousness" is used, and unpack (list) some of the different ideas that we talk about
when we use the word.

# Problem 6 (Ch 5)

Specify the four critics (corrector, suppressor, censor and encourager [p86])
in this story:

"Joan is applying for a job at two AI companies, 'Intelligence Vacuum' and 
'Emergent Design', and begins to write applications. In her first email, she 
discusses her credentials, education and a question about her salary.  After 
she sends the email, she reflects and concludes that it was premature to 
discuss financial issues.  Joan begins her next email, this time she only 
includes education and her credentials.  In the credentials section, she 
sees a great opportunity for a joke and lists her programming skills, "LISP,
C and SNOBOL," under the title 'Foreign Languages.' Impressed with her humor,
she thinks about inserting an emoticon ':-)' but does not. Ending her email, 
she misspells her name and then quickly corrects it before sending."

# PS 6 2007 #


Lecture 7: Problem Set 6 (Due Wednesday April 4th, 7:00PM)


 Reading: (a) Emotion Machine, Chapter 5
          (b) EM-ONE: An architecture for reflective commonsense thinking, 11-26.

 Problem 1

   In order to find meaningful answers you must first be able to formulate good 
   questions.  List ten questions you would like to answer about Chapter 5.


 Problem 2
    
   In this chapter, Minsky describes the layers of Model-6.  These layers are
   useful for categorizing thought processes--i.e. self-reflective layers focus
   on debugging and building models of the system's own abilities and
   limiations.

      a) List 5 reasons why developing a way to classify thought processes 
         can be useful. 


 Problem 3
     
   In class,  Marvin has described his experience with learning how to play
   chess where, as a beginner, moving the knight required interpreting rules.
   With more experience, he was able to visualize the appropriate 8 positions
   'immediately'.

      a) In psychology, this phenomenon is known as chunking; and in computer
        science: compiling.  Describe another type of learning where this 
        takes place and relate it aspects of compiling software.

      b) In Cyc, unlike people its reasoning performance does not improve
        with repetition. What could you add to Cyc to give it this ability?

 Problem 4
       
   In the section on Learned Reactions, Minsky describes how IF->DO rule
   alone are not enough because there are always exceptions for each rule, 
   which would make the assertion false. 

     a) What benefits does adding 'THEN' to IF->DO rules provide?

     b) Describe a process that would allow a knowledge base to keep a useful
       rule even though it has many exceptions. 

 Problem 5

    A big problem with using rules as a representation is knowing the level
    of descriptions to include within the conditional.  If the description is
    to vague/ambiguous, it may match too many cases; however, if it is too 
    specific or precise, it may never match another situation!
	
    Commonsense knowledge consists of generalizations;, there are often
    exceptions for each assertion or rule, and  commonsense knowledge is
    densely interconnected.  Because of this, it is indirect to talk about
    assertions being 'true' or 'false' without describing context or the 
    desired inference. Instead, we can characterize knowledge as 'useful' 
    within the context of solving a specific problem.

      a) Take a look at the first 500 entries in the OpenMind project,
        http://web.media.mit.edu/~dustin/6.868/omcs-h500.txt , choose 
        your favorite 5 assertions and describe problem contexts in which 
        that knowledge would be useful for solving the problem.
	[Answering questions is one type of problem solving]
	



# PS 7 2007 #



Reading: Emotion Machine, Chapter 6


Problem 1

  In order to find meaningful answers you must first be able to formulate
  good questions.  List ten questions you would like to answer about
  Chapter 6.


Problem 2

  You could think of scripts as compiled plans.

    a) Write a script for going to a restaurant as a sequence of actions.
       For an example of a script, see pg. 192-3.

    b) List the transframes in each applicable mental realm (the Panalogy 
       representation) for each step of the script.

    c) Imagine now that you are trying to plan for cooking some food at home.
       Do the same thing you did in parts (a,b) for this second plan.

    d) Now list the similarities and differences between the panalogies in
       your two scripts.  This will form a matrix-like structure.

 Note that the process of adapting the second plan from the first
 script,  by analogy,  could be described as actions within a
 reflective-level script!


Problem 3

  Imagine a situation in which you are hungry.  
 
    a) List what this knowledge would look like (e.g., your goals,  
       your environment). Consider this knowledge to be reactive. 
   
    b) Describe two deliberative level critics that can select between 
       these two eating-plans from Problem 2  using some of the knowledge 
	 in the reactive level.
	

# PS 8 2007 #



Problem 1

  In order to find meaningful answers you must first be able to formulate
  good questions.  List ten questions you would like to answer about
  Chapter 7.


Problem 2

  On pg. 229-230, Minsky lists examples of critics and selectors for
  the top 4 layers (deliberative, reflective, self-reflective, and
  self-conscious).  For example, in the deliberative layer, "An
  action did not achieve the expected effect" is a critic, while
  "Find a better way to predict" is a selector that this critic
  activates.

    a) For each of these four layers, list two additional
       critic-selector pairs.

    b) Describe a way to activate a common Emotion as a way to think,
       such as Anger, Compassion, Pity, Empathy, or Sympathy, in terms
       of description of critic-selector pairs.

    c) Think about implementing a critic. What would it mean for the
       critic to be 'activated'.  Explain how this could be done
       and what other computational resources would be required. (For
	     ideas, consult Push Singh's PhD thesis.)


Problem 3

  Section 7-4 discusses many different examples of useful ways to think.

    a) Choose your favorite three of these ways to think and give an example
       of each.

    b) Think of your own problem that can't be solved by any of these ways to
       think.

    c) Describe a new way to think that can solve this problem.


Problem 4

  Solving the problems in this problem set could be considered an intelligent
  task.

    a) Describe at least three critic-selector pairs that helped you to solve
       the problems in this problem set.

    b) Try to categorize the critics and selectors of part (a) into the
       layers of Model-6.  Discuss why you chose the classification for each
       critic or selector resource.


# PS 9 2007



Problem 1

  In order to find meaningful answers you must first be able to formulate
  good questions.  List ten questions you would like to answer about
  Chapter 8.


Problem 2

  Credit-assignment processes decide what is important to learn or
  remember.  Allan Newell, quoted on page 273, describes how the
  success or failure of a method by itself is not enough information
  for quick learning to occur.  Instead, each small step within the
  a larger context of methods must be considered in learning.
  Minsky goes on to describe how credit must be assigned to each of
  the different levels of goals and methods depending on what
  methods were responsible for the success or failure in the current
  context.  If reflective-level critics can detect complex
  arrangements of failure or success states, there can deploy very
  specific techniques to maximize what is learned from a single
  problem-solving experience.

  a) Consider a problem solving situation in which you have a small
     set of knowledge representations and a collection of successful
     If-Do reactions.  Describe a simple problem domain for these
     successful If-Do reactions.

  b) Describe in detail the If condition and the Do action of four
     of these If-Do reaction rules.

  c) Describe a slightly novel learning situation in which one of
     these If-Do reaction rules now fails.  Explain what changes or
     additions should be made to your rules in order to remember
     this failure and react accordingly in the future. 

  d) Classify the type of failure (See Singh 2003 [1] for ideas)
     and describe how a credit assignment process could detect
     and fix this error.

     [1] http://web.media.mit.edu/~push/ReflectiveCritics.html

  (Extra-Credit)

     Describe a scheme of how success could turn interpreted rules
     into 'compiled rules'.


Problem 3

  Using multiple representations that have panalogies for quickly
  switching from one representation to another is a very adaptable
  technique for solving problems.  A panalogy can be used to quickly
  translate the problem into another mental realm when one way of
  thinking gets stuck.  Problem solving can then make further
  progress in this new mental realm's way of thinking.

  a) Stories, Scripts, Semantic Networks, Trans-Frames, K-Lines, and
     Micronemes are a few specific examples of representations that
     could be used in different ways of thinking.  Associate each
     representation with a few types of problems those structures
     make problems easy to solve.  (Hint: The power of a
     representation does not only come from *what* it can possibly
     represent, but how easily it can be used to solve problems and
     how the representation can be constructed by another processes
     involved with learning and refining representations.)

  b) Describe a problem solving situation where using one of these
     representations might get stuck at finding a solution.

  c) Explain how using a panalogy can translate a stuck problem
     state into a different realm's way of thinking that allows the
     stuck way of thinking to successfully make further progress
     toward a solution in the second realm.

  d) A desk can be viewed as furniture, chair, property, a
     collection of wood, and so on.  What parts of the EM
     architecture would be responsible for selecting these
     representations.  Ground your argument in a specific problem
     solving example.


\bibliographystyle{acm}
\bibliography{/bib/papers}
