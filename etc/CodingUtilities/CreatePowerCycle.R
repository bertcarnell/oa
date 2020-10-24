# code to modify existing Galois Field generating polynomials into
#   c++ for the new structure while minimizing mistakes

require(stringr)
require(magrittr)

filename <- file.path("../../original/oa_c.txt")
stopifnot(file.exists(filename))

X <- readLines(filename)

ind_begin <- 6074 
ind_end <- 7414 

Y <- X[ind_begin:ind_end] %>%
  stringr::str_remove("X") %>%
  stringr::str_remove("[/][*].*[*][/]") %>%
  stringr::str_remove(";") %>%
  stringr::str_remove(".*ivector.*")

q <- list(list(p = 2, n = 2:29),
          list(p = 3, n = 2:18),
          list(p = 5, n = 2:12),
          list(p = 7, n = 2:10),
          list(p = 11, n = 2:8),
          list(p = 13, n = 2:8),
          list(p = 17, n = 2:7),
          list(p = 19, n = 2:7),
          list(p = 23, n = 2:6),
          list(p = 29, n = 2:6),
          list(p = 31, n = 2:6),
          list(p = 37, n = 2:5),
          list(p = 41, n = 2:5),
          list(p = 43, n = 2:5),
          list(p = 47, n = 2:5)
)

temp <- lapply(q, function(x)
{
  p = x$p
  n = x$n
  return(paste0("xtn", p, "t", n, "[[]"))
})

locations <- lapply(temp, function(x)
{
  c(sapply(x, function(z) grep(z, Y)))
})

outputlines <- NULL
outputlines[1] <- "/*"
outputlines[2] <- " * NOTE: This file should be excluded from the Doxygen build"
outputlines[3] <- " ****** COMPUTER GENERATED etc/CreatePowerCylce.R ******" 
outputlines[4] <- " *" 
outputlines[5] <- " * file xtn.h"
outputlines[6] <- " * author Robert Carnell"
outputlines[7] <- " * copyright Copyright (c) 2020, Robert Carnell"
outputlines[8] <- " *"
outputlines[9] <- " * License:  MIT"
outputlines[10] <- " *"
outputlines[11] <- " * Reference:"
outputlines[12] <- ' * <ul><li><a href="http://lib.stat.cmu.edu/designs/">Statlib Designs</a></li>'
outputlines[13] <- ' * <li><a href="http://lib.stat.cmu.edu/designs/oa.c">Owen\'s Orthogonal Array Algorithms</a></li></ul>'
outputlines[14] <- " * "
outputlines[15] <- " * This file is derived from the xtndispatch.h xtnset.h xtndeclare.h"
outputlines[16] <- " * "
outputlines[16] <- " * See Table B.3 Power cycle II pg 316 in Block Designs:  A Randomization Approach"
outputlines[17] <- " */"
outputlines[18] <- ""
outputlines[19] <- "#ifndef XTN_H"
outputlines[20] <- "#define XTN_H"
outputlines[21] <- ""

makePolynomial <- function(n, W)
{
  term1 <- paste0("x^", n, " = ")
  for (i in 1:length(W))
  {
    if (i == 1 && W[i] != 0) 
    {
      term2 <- W[i]
    } else if (i == 2 && W[i] != 0)
    {
      term2 <- c(term2, paste0(ifelse(W[i] == 1, "", W[i]), "x"))
    } else if (W[i] != 0)
    {
      term2 <- c(term2, paste0(ifelse(W[i] == 1, "", W[i]), "x^", i - 1))
    }
  }
  return(paste0(term1, paste0(term2, collapse = " + ")))
}

#makePolynomial(10, c(1,2,3,0,0,4,5,1,0,0))

for (i in seq_along(q))
{
  p <- q[[i]]$p
  for (j in seq_along(q[[i]]$n))
  {
    n <- q[[i]]$n[j]
    Z <- Y[unlist(locations[[i]][j])]
    W <- sapply(Z, function(x) trimws(unlist(strsplit(x, split = " = "))[2]))
    lenW <- length(W)
    stopifnot(length(W) == n)
    outputlines <- c(outputlines, paste0("// GF(", p, "^", n, ") = GF(", p^n, ")"))
    outputlines <- c(outputlines, paste0("// ", makePolynomial(n, W)))
    outputlines <- c(outputlines, paste0(ifelse(i == 1 & j == 1, "if", "else if"), 
                                         " (q == primes::ipow(", p, ",", n, 
                                         ")) xtn = {", paste0(W, collapse = ", "), 
                                         "};"))
  }
}

outputlines <- c(outputlines, "#endif")

writeLines(outputlines, file.path("../../src/oalib/xtn.h"))

