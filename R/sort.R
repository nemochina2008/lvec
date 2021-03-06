
#' Sort a lvec
#'
#' @param x lvec to sort
#' @param decreasing unused (a value unequal to \code{FALSE} will generate an error).
#' @param clone clone x before sorting
#' @param ... unused.
#'
#' @return
#' Sorts \code{x} and returns a sorted copy of \code{x}. When \code{clone} is 
#' \code{FALSE} the input vector is modified.
#'
#' @examples
#' x <- as_lvec(rnorm(10))
#' sort(x)
#'
#' # Effect of clone
#' a <- as_lvec(rnorm(10))
#' b <- sort(a, clone = FALSE)
#' print(a)
#'
#' @useDynLib lvec
#' @export
sort.lvec <- function(x, decreasing = FALSE, clone = TRUE, ...) {
  if (decreasing != FALSE) stop("decreasing is not supported yet.")
  if (!is_lvec(x)) stop("x should be of type lvec.")
  if (clone) x <- clone(x)
  .Call("sort", x)
  x
}

