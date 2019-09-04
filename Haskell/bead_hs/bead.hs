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

solve l = recSolve l (emptyTable (length (fst l)) (length (snd l)))