# storagebins
This is my solution to a problem my wife saw on a facebook post.  It's a perfect [ProjectEuler](https://projecteuler.net/)-style problem, so I figured I'd solve it both analytically and verify with a program.

****Problem****
There are four colors of buckets.  For each color, there are two single-width buckets ("singles") and one double-width bucket ("doubles").  (So, for example, you have one 2-unit wide green buckets and two 1-unit green buckets.)  Four colors, three buckets apiece, gives a total of 12 buckets.

![alt text][Rack]

There is a rack with four shelves, each shelf holding a total width of four units.  How many unique arrangements can you make such that all buckets are used, all shelves are full?

****Solution****

**First, ignore colors completely** and enumerate the possible arrangements only in terms of bucket sizes.  The various arrangements are:

| Type      | Composition          |  Visually               |
| --------- |:--------------------:| -----------------------:|
| `I`       | 4 singles            |  ![alt text][TypeIg]    |
| `II`      | 2 doubles            |  ![alt text][TypeIIg]   |
| `III`     | 1 double + 2 singles |  ![alt text][TypeIIIg]  |

There are constraints on the combinations of rows possible.  (E.g., we cannot have four rows of type `I`).  We can just enumerate the possibilities, ignoring order (for now):

* (1) `I`, `I`, `II`, `II`   (all four doubles on two shelves)
* (2) `I`, `II`, `III`, `III`  (two doubles on one shelf, other two on separate shelves)
* (3) `III`, `III`, `III`, `III`  (Each shelf has one double)

Now we can count the row permutations of each of the above.  For any case where type `III` is used, we add a factor of `3`, since there are three distinct orderings for type `III`:  (![alt text][TypeIIIa],  ![alt text][TypeIIIb],  or  ![alt text][TypeIIIc])
* (1) there are `(4 choose 2) = 6` ways.
* (2) there are `(4! / 2) = 12` ways - `4!` but then divide by `2` only to avoid double-counting the `III`s.  _But then_ we multiply by `9` to account for the variations in type `III` arrangements on the two shelves.  So we use `12*9 = 108`.
* (3) all shelves are type `III`, each shelf has 3 variations.  `3*3*3*3 = 81`

The total ways to arrange the buckets, ignoring colors is 

`6 + 108 + 81 = 195`.

Next, for each of the 195 shape-arrangements above, we **account for color ordering variations**.

To make this "simple", we can count the colorings of the doubles separately from the colorings of the singles, then take the product (since they're independent):

* **doubles:**  This one's simple:  `4! = 24`
* **singles:**  Basically, we're asking how many ways you can arrange 1,1,2,2,3,3,4,4 ?  
The answer is to use the *multinomial coefficient*, `(8 choose 2,2,2,2) = 40320/(2*2*2*2) = 2520`.  
(Multinomial coefficients are similar to binomial coefficients, "P choose Q", but a bit more involved.  See [wikipedia's explanation](https://en.wikipedia.org/wiki/Multinomial_theorem#Ways_to_put_objects_into_bins) or this [good youtube video](https://www.youtube.com/watch?v=rYtzhc2snj4) ).

The product is `24 * 2520 = 60,480`
Multiply this by the number of "shape arrangements" above:

`195 * 60,480 =`

**`11,793,600`**

****Brute Force Verification****

The C++ program in this repo yields the same solution by brute-force.

**Approach**

Using [Heap's Algorithm](https://en.wikipedia.org/wiki/Heap%27s_algorithm), consider **all possible orderings of the 12 buckets**.  For each ordering, check if:

1. Each shelf contains a total of 4 units - i.e., You cannot have a single followed by two doubles on a shelf.
2. To avoid double-counting when, e.g., two orderings differ only because two like-colored single buckets are switched, we have IDs for all 12 buckets, such that `ID0` and `ID1` are the pair of color #1, `ID3` and `ID4` are the pair of color #2, etc.  If we see the ordering have `ID0` come after `ID1` (or `ID3` after `ID4`, etc, etc), we do not count the ordering as valid.  (Maybe my explanation isn't clear, but I could make a smaller example to demonstrate this.  :-)

Anyway, as we go through all `12!` permutations of the buckets, and tally up each time the above are met, we get the same answer, **`11,793,600`**

[TypeI]: https://raw.githubusercontent.com/jesseconnell/storagebins/master/images/Type_I.png "TypeI - s s s s"
[TypeII]: https://raw.githubusercontent.com/jesseconnell/storagebins/master/images/Type_II.png "TypeII - D D"
[TypeIIIa]: https://raw.githubusercontent.com/jesseconnell/storagebins/master/images/Type_IIIa.png "TypeIIIa - D s s"
[TypeIIIb]: https://raw.githubusercontent.com/jesseconnell/storagebins/master/images/Type_IIIb.png "TypeIIIb - s D s"
[TypeIIIc]: https://raw.githubusercontent.com/jesseconnell/storagebins/master/images/Type_IIIc.png "TypeIIIc - s s D"
[TypeIg]: https://raw.githubusercontent.com/jesseconnell/storagebins/master/images/Type_Ig.png "TypeIg"
[TypeIIg]: https://raw.githubusercontent.com/jesseconnell/storagebins/master/images/Type_IIg.png "TypeIIg"
[TypeIIIg]: https://raw.githubusercontent.com/jesseconnell/storagebins/master/images/Type_IIIg.png "TypeIIIg"
[Rack]: https://raw.githubusercontent.com/jesseconnell/storagebins/master/images/Rack.png "Rack"
