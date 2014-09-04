my.rhclean <- function (temp = rhoptions()$HADOOP.TMP.FOLDER)
{
    if (is.null(temp))
        stop("No Temporary Folder Provided")
    else {
        ## get my user name
        myname <- system("whoami", intern=TRUE)
        files <- rhls(rhoptions()$HADOOP.TMP.FOLDER)$file
        myfiles <- rhls(rhoptions()$HADOOP.TMP.FOLDER)$owner == myname
        files <- files[grepl("/rhipe-temp-", files) & myfiles]
        if (length(files) > 0) {
            rhdel(files)
            message(sprintf("Deleted %s file%s", length(files),
                if (length(files) > 1)
                  "s"
                else ""))
        }
        else {
            message("Nothing to delete")
        }
    }
}
