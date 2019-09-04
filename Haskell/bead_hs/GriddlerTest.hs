import Data.List (transpose)	

type Cell     = Char
type Table    = [[Cell]]
type ClueLine = [Int]
type Clues    = ([ClueLine], [ClueLine])

unknown = 'u'
empty   = 'e'
full    = 'f'

duckClues  = (duckRows, duckCols)    :: Clues
poundClues = (poundRows,  poundCols) :: Clues

duckRows = [[3], [5], [4,3], [7], [5], [3], [5], [1,8],
            [3,3,3], [7,3,2], [5,4,2], [8,2], [10], [2,3], [6]]

duckCols = [[3], [4], [5], [4], [5], [6], [3,2,1], [2,2,5],
            [4,2,6], [8,2,3], [8,2,1,1], [2,6,2,1], [4,6], [2,4], [1]]


poundRows = [[4], [2,1], [1,2], [2,2], [2], [8], [2], [8],
             [2], [2], [2,2,2], [6,3], [2,5,3], [2,2,6], [4,4]]

poundCols = [[2],[4],[2,1],[1,1,2,1],[1,1,4],[11],[12],
             [2,1,1,2],[1,1,1,3],[1,1,1,2],[1,1,1,2],[3,3],[2,3],[3],[2]]

yinYangClues :: Clues
yinYangClues = (yinYangRows, yinYangCols)

yinYangRows = [[8],[4,4],[2,6],[1,3,2],[3,3],[8],[6],[2,5],
               [1,2,4],[2,5],[4,5],[8]]
yinYangCols = [[4,4],[3,3],[2,2],[2,2,2],[1,3,2,1],[1,4,2],
               [7,3],[3,7],[2,6],[10],[8],[4]]

flowerClues :: Clues
flowerClues = (flowerRows, flowerCols)

flowerRows = [[2,2],[1,1,1],[1,1,1],[1,5,2],[1,2,2,1],[1,5,1],
              [2,1,3],[2,2],[1],[2,1,2],[3],[1]]
flowerCols = [[2],[1,1],[2,1],[1,3,1,1],[1,3,1,1],[3,2,1],[1,3,5],
              [1,3,1,1],[2,1,1],[1,1,1],[1,1],[2]]		  

showCell :: Cell -> Char

showCell 'u' = '?'
showCell 'e' = ' '
showCell 'f' = '#'

showRow :: [Cell] -> String

showRow l = '|' : [showCell x | x <- l ] ++ "|\n"

showTable :: Table -> String

showTable [l] = showRow l
showTable [] = []
showTable (l@(x:xs):ls) = (showRow l) ++ showTable ls

empties :: Int -> [Cell]

empties n = take n (repeat 'e')

fulls :: Int -> [Cell]

fulls n = take n (repeat 'f')

placeOneBlock :: Int -> Int -> [[Cell]]

placeOneBlock n m = [ (empties x ++ fulls n) ++ empties (m-x-n) | x <- [0..(m-n)] ]

emptyLineOptions :: ClueLine -> Int -> [[Cell]]

emptyLineOptions [] y
             | y == 0 = [[]]
             | y > 0  = [empties y] 
emptyLineOptions [x] y = placeOneBlock x y
emptyLineOptions l@(x:xs) y
             | sum l >= y = []
             | otherwise = [empties z ++ fulls x ++ empties 1 ++ n | z <- [0..(y-(sum l)-1)], n <- emptyLineOptions xs (y-x-1-z)]
			 
isMatching :: Cell -> Cell -> Bool

isMatching 'f' 'u' = False
isMatching 'f' 'e' = False
isMatching 'e' 'u' = False
isMatching 'e' 'f' = False
isMatching _ _ = True

lineOptions :: ClueLine -> [Cell] -> [[Cell]]

lineOptions [] l2 = [empties (length l2)]
lineOptions l1 l2 = [ n | n <- emptyLineOptions l1 (length l2), and[(isMatching (fst a) (snd a)) || fst a == 'u' || snd a =='u' | a <- zip n l2 ] ]

combineOption :: Cell -> Cell -> Cell

combineOption 'f' 'f' = 'f'
combineOption 'e' 'e' = 'e'
combineOption _ _ = 'u'

combineLineOptions :: [[Cell]] -> [Cell]

combineLineOptions [(x:xs)] = (x:xs)
combineLineOptions (x:xs) = zipWith combineOption x (combineLineOptions xs)

reduceLine :: ClueLine -> [Cell] -> [Cell]

reduceLine [] l = l
reduceLine l1 l2 
             | lineOptions l1 l2 /= [] = combineLineOptions (lineOptions l1 l2)
             | otherwise = l2
			 
reduceRows :: [ClueLine] -> Table -> Table

reduceRows l1 l2 = [reduceLine (fst z) (snd z) | z <- (zip l1 l2) ]

reduceTable :: Clues -> Table -> Table

reduceTable clues table = transpose(reduceRows (snd clues) (transpose(reduceRows (fst clues) table)))

emptyTable :: Int -> Int -> Table

emptyTable n m = [ replicate m 'u' | a <- [1..n] ]

recSolve :: Clues -> Table -> Table

recSolve l1 l2 
          | reduceTable l1 l2 == l2 = reduceTable l1 l2
          | otherwise = recSolve l1 (reduceTable l1 l2)
		  
solve :: Clues -> Table

solve l = recSolve l (emptyTable (length (fst l)) (length (snd l))) -- Ide másold be a megoldásod!



{-
A megodott konstansok segítségével tudod külön-külön tesztelni a
függvényeidet, vagy a testAll függvénnyel az összes tesztet le tudod
futtatni egyszerre.
-}

-- =============================== -Tesztesetek- =========================

testShowCell = [showCell unknown == '?', showCell empty == ' ', showCell full == '#']

testShowRow = [showRow [unknown, empty, full] == "|? #|\n", showRow [unknown, empty, unknown] == "|? ?|\n" ,showRow [empty, empty, full] == "|  #|\n", showRow [empty, full, full] == "| ##|\n"]


testShowTable = [showTable ([] :: [[Cell]]) == "",showTable [[full, empty, unknown, empty, full]] == "|# ? #|\n",showTable [[full, empty, unknown, empty, full], [empty, full, full, empty, full]] == "|# ? #|\n| ## #|\n",showTable (solve duckClues) == "|         ###   |\n|        #####  |\n|       #### ###|\n|       ####### |\n|        #####  |\n|         ###   |\n|        #####  |\n|#     ######## |\n|###  ###   ### |\n|####### ### ## |\n| ##### #### ## |\n| ########  ##  |\n|  ##########   |\n|    ## ###     |\n|      ######   |\n",showTable (solve poundClues) == "|       ####    |\n|      ##   #   |\n|      #    ##  |\n|     ##    ##  |\n|     ##        |\n|   ########    |\n|     ##        |\n|   ########    |\n|     ##        |\n|     ##        |\n|  ## ##      ##|\n| ######     ###|\n|##  #####  ### |\n|##  ## ######  |\n| ####   ####   |\n"]


testEmptyLineOptions = [emptyLineOptions [5,6,7] 15 == [],emptyLineOptions [] 0 == [""],emptyLineOptions [] 10 ==["eeeeeeeeee"],emptyLineOptions [15] 15 == ["fffffffffffffff"],emptyLineOptions [1] 10 == ["feeeeeeeee","efeeeeeeee","eefeeeeeee","eeefeeeeee","eeeefeeeee","eeeeefeeee","eeeeeefeee","eeeeeeefee","eeeeeeeefe","eeeeeeeeef"],emptyLineOptions [1,1] 7 == ["fefeeee","feefeee","feeefee","feeeefe","feeeeef","efefeee","efeefee","efeeefe","efeeeef","eefefee","eefeefe","eefeeef","eeefefe","eeefeef","eeeefef"],emptyLineOptions [2] 5 == ["ffeee","effee","eeffe","eeeff"],emptyLineOptions [1,2] 5 == ["feffe","feeff","efeff"],emptyLineOptions [10] 15 == ["ffffffffffeeeee","effffffffffeeee","eeffffffffffeee","eeeffffffffffee","eeeeffffffffffe","eeeeeffffffffff"],emptyLineOptions [3, 4, 4] 15 == ["fffeffffeffffee","fffeffffeeffffe","fffeffffeeeffff","fffeeffffeffffe","fffeeffffeeffff","fffeeeffffeffff","efffeffffeffffe","efffeffffeeffff","efffeeffffeffff","eefffeffffeffff"]]


testLineOptions = [lineOptions ([] :: [Int]) (replicate 10 unknown) == ["eeeeeeeeee"], lineOptions [10] (replicate 15 unknown) ==["ffffffffffeeeee","effffffffffeeee","eeffffffffffeee","eeeffffffffffee","eeeeffffffffffe","eeeeeffffffffff"],lineOptions [3, 4, 4] (replicate 15 unknown) == ["fffeffffeffffee","fffeffffeeffffe","fffeffffeeeffff","fffeeffffeffffe","fffeeffffeeffff","fffeeeffffeffff","efffeffffeffffe","efffeffffeeffff","efffeeffffeffff","eefffeffffeffff"],lineOptions [10] (replicate 2 unknown ++ [empty] ++ replicate 13 unknown) == ["eeeffffffffffeee","eeeeffffffffffee","eeeeeffffffffffe","eeeeeeffffffffff"],lineOptions [3, 4, 4] ([empty] ++ replicate 13 unknown ++ [empty]) == ["efffeffffeffffe"],lineOptions [10] (replicate 2 unknown ++ [full] ++ replicate 13 unknown) == ["ffffffffffeeeeee","effffffffffeeeee","eeffffffffffeeee"],lineOptions [3, 4, 4] ([full] ++ replicate 13 unknown ++ [full]) == ["fffeffffeeeffff","fffeeffffeeffff","fffeeeffffeffff"]]

testCombineOption = [combineOption full  full == 'f',combineOption empty empty == 'e',combineOption full  unknown == 'u',[combineOption i j | i <- [full, empty, unknown], j <- [full, empty,  unknown]] == "fuuueuuuu"]


testCombineLineOptions = [combineLineOptions (lineOptions ((fst poundClues) !! 5) (replicate 15 unknown)) == "uuuuuuufuuuuuuu",combineLineOptions (lineOptions ((snd poundClues) !! 5) (replicate 15 unknown)) =="uuuufffffffuuuu",combineLineOptions (lineOptions ((fst duckClues)  !! 5) (replicate 15 unknown)) == "uuuuuuuuuuuuuuu",combineLineOptions (lineOptions ((fst duckClues)  !! 7) (replicate 15 unknown)) == "uuuuuuufffuuuuu",combineLineOptions (lineOptions ((snd duckClues)  !! 9) (replicate 15 unknown)) == "ffffffffeffefff",combineLineOptions ["ffffffffffeeeeee", "effffffffffeeeee", "eeffffffffffeeee"] == "uuffffffffuueeee", combineLineOptions ["fffeffffeeeffff", "fffeeffffeeffff", "fffeeeffffeffff"] == "fffeuuffuueffff",combineLineOptions (lineOptions [10] (replicate 2 unknown ++ [full] ++ replicate 13 unknown)) == "uuffffffffuueeee",combineLineOptions (lineOptions [3, 4, 4] ([full] ++ replicate 13 unknown ++ [full])) == "fffeuuffuueffff", [combineLineOptions (lineOptions l (replicate 15 unknown)) | l<- (fst poundClues ++ snd poundClues)] == ["uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuufuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuufuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuufuuuuuuuuu","uuuuuuffuuuuuuu","uuuuuuuuufffuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuufffffffuuuu","uuufffffffffuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu"]]

testReduceLine = [reduceLine ((fst poundClues) !! 5) (replicate 15 unknown) == "uuuuuuufuuuuuuu",reduceLine ((snd poundClues) !! 5) (replicate 15 unknown) == "uuuufffffffuuuu",reduceLine ((fst duckClues)  !! 5) (replicate 15 unknown) =="uuuuuuuuuuuuuuu",reduceLine ((fst duckClues)  !! 7) (replicate 15 unknown) =="uuuuuuufffuuuuu",reduceLine [] ['f', 'f', 'f'] =="fff",reduceLine ((snd duckClues)  !! 9) (replicate 15 unknown) == "ffffffffeffefff", [reduceLine i (replicate 15 unknown) | i <- fst duckClues ++ snd duckClues ] == ["uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuufffuuuuu","uuuuuuuuuuuuuuu","uffffffuuffuufu","uufffuuuffuuuuu","uuuuffffuuuuuuu","uuuuufffffuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuufuuuu","ufffuufuufffffu","ffffffffeffefff","ffffffffeffefef","ufuufffffuufuuu","uuuuuuuuuffuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu"], [reduceLine i (replicate 15 unknown) | i <- fst poundClues ++ snd poundClues ] == ["uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuufuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuufuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuufuuuuuuuuu","uuuuuuffuuuuuuu","uuuuuuuuufffuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuufffffffuuuu","uuufffffffffuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu"], [reduceLine ((snd duckClues)  !! 8) ((take i (replicate 15  unknown)) ++ [full] ++ (drop (i+1) (replicate 15  unknown))) | i <- [0..14]] == ["ffffeufuufffffu","ufffuufuufffffu","ufffuufuufffffu","ufffuufuufffffu","effffeffeffffff","ffffeffeufffffu","ufffuufuufffffu","ufffueffeffffff","ffffeffeffffffe","ufffuufuufffffu","ufffuufuufffffu","ufffuufuufffffu","ufffuufuufffffu","ufffuufuufffffu","ufffuufueffffff"], [reduceLine ((snd duckClues)  !! 8) ((take i (replicate 15  unknown)) ++ [empty] ++ (drop (i+1) (replicate 15  unknown))) | i <- [0..14]] == ["effffeffeffffff","ueuuuuuuuuuuuuu","uueuuuuuuuuuuuu","uuueuuuuuuuuuuu","ffffeufuufffffu","ufffueffeffffff","uuuuuueuuuuuuuu","ffffeffeufffffu","ufffuufueffffff","uuuuuuuuueuuuuu","uuuuuuuuuueuuuu","uuuuuuuuuuueuuu","uuuuuuuuuuuueuu","uuuuuuuuuuuuueu","ffffeffeffffffe"]]


testReduceRows = [reduceRows (fst duckClues)  (emptyTable 15 15) == ["uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuufffuuuuu","uuuuuuuuuuuuuuu","uffffffuuffuufu","uufffuuuffuuuuu","uuuuffffuuuuuuu","uuuuufffffuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu"], reduceRows (fst duckClues)  (emptyTable 15 15) == ["uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuufffuuuuu","uuuuuuuuuuuuuuu","uffffffuuffuufu","uufffuuuffuuuuu","uuuuffffuuuuuuu","uuuuufffffuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu"],reduceRows (fst poundClues) (emptyTable 15 15) == ["uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuufuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuufuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuufuuuuuuuuu","uuuuuuffuuuuuuu","uuuuuuuuufffuuu","uuuuuuuuuuuuuuu"],reduceRows (snd poundClues) (emptyTable 15 15) == ["uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuufffffffuuuu","uuufffffffffuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu"]]

testReduceTable = [reduceTable duckClues  (emptyTable 15 15) == ["ueeeeeeuuffuuuu","ueeeeeeuffffuuu","ueeeeeeufffuuuu","ueeeeeeufffuuuu","ueeeeeeuufffuuu","ueeeeeeuefffuuu","uuueeeeuffffuuu","uuuuuuffffffuuu","uuuuuufueeefuuu","uffffffufffuffu","uuffffeffffufuu","uuuufffffeefuuu","uuuuuffffffuuuu","ueueuuefffeuuuu","ueeeeufufffuuuu"],reduceTable poundClues (emptyTable 15 15) == ["uuuuueeuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuufuuuuuuuu","uuuuuffuuuuuuuu","uuuuufffuuuuuuu","uuuuuffeuuuuuuu","uuuuufffuuuuuuu","uuuuuffeuuuuuuu","uuuuuffuuuuuuuu","uuuuuffuuuuuuuu","uuuuuffuuuuuuuu","uuuuuuffuuufuuu","uuuuuuuuufffuuu","uuuuuuueuuuuuuu"]]

testEmptyTable = [emptyTable 5 5 == ["uuuuu","uuuuu","uuuuu","uuuuu","uuuuu"],emptyTable 15 15 == ["uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu","uuuuuuuuuuuuuuu"], [emptyTable i j | i <- [3..5], j <- [3..5] ] == [["uuu","uuu","uuu"],["uuuu","uuuu","uuuu"],["uuuuu","uuuuu","uuuuu"],["uuu","uuu","uuu","uuu"],["uuuu","uuuu","uuuu","uuuu"],["uuuuu","uuuuu","uuuuu","uuuuu"],["uuu","uuu","uuu","uuu","uuu"],["uuuu","uuuu","uuuu","uuuu","uuuu"],["uuuuu","uuuuu","uuuuu","uuuuu","uuuuu"]]]

testRecSolve = [recSolve duckClues (emptyTable 15 15) == ["eeeeeeeeefffeee","eeeeeeeefffffee","eeeeeeeffffefff","eeeeeeefffffffe","eeeeeeeefffffee","eeeeeeeeefffeee","eeeeeeeefffffee","feeeeeffffffffe","fffeefffeeefffe","fffffffefffeffe","efffffeffffeffe","effffffffeeffee","eeffffffffffeee","eeeeffefffeeeee","eeeeeeffffffeee"], recSolve poundClues (emptyTable 15 15) == ["eeeeeeeffffeeee","eeeeeeffeeefeee","eeeeeefeeeeffee","eeeeeffeeeeffee","eeeeeffeeeeeeee","eeeffffffffeeee","eeeeeffeeeeeeee","eeeffffffffeeee","eeeeeffeeeeeeee","eeeeeffeeeeeeee","eeffeffeeeeeeff","effffffeeeeefff","ffeefffffeefffe","ffeeffeffffffee","effffeeeffffeee"]]

testSolve = [solve duckClues == ["eeeeeeeeefffeee","eeeeeeeefffffee","eeeeeeeffffefff","eeeeeeefffffffe","eeeeeeeefffffee","eeeeeeeeefffeee","eeeeeeeefffffee","feeeeeffffffffe","fffeefffeeefffe","fffffffefffeffe","efffffeffffeffe","effffffffeeffee","eeffffffffffeee","eeeeffefffeeeee","eeeeeeffffffeee"], solve poundClues == ["eeeeeeeffffeeee","eeeeeeffeeefeee","eeeeeefeeeeffee","eeeeeffeeeeffee","eeeeeffeeeeeeee","eeeffffffffeeee","eeeeeffeeeeeeee","eeeffffffffeeee","eeeeeffeeeeeeee","eeeeeffeeeeeeee","eeffeffeeeeeeff","effffffeeeeefff","ffeefffffeefffe","ffeeffeffffffee","effffeeeffffeee"]]

testAll = map and [testShowCell,testShowRow,testShowTable,testEmptyLineOptions,testLineOptions,testCombineOption,testCombineLineOptions,testReduceLine,testReduceRows,testReduceTable,testEmptyTable,testRecSolve,testSolve]
