allDec <- read.csv("heatALLdec.csv", sep=";")
allEnc <- read.csv("heatALLenc.csv", sep=";")
allSig <- read.csv("heatALLsig.csv", sep=";")

plotit <- function(file, data, main, xlab, ylab) {
    pdf(file)
    plot(data[,1], data[,2], pch=3, main=main, xlab=xlab, ylab=ylab, col="black");
    dev.off()
}

plotit("heatdec.pdf", allDec, "wc_ecc_decrypt()", "EC key bytes", "Time to generate [microseconds]")
plotit("heatenc.pdf", allEnc, "wc_ecc_encrypt()", "EC key bytes", "Time to generate [microseconds]")
plotit("heatsig.pdf", allSig, "wc_ecc_sign_hash()", "EC key bytes", "Time to generate [microseconds]")
