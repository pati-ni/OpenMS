from MSExperiment  cimport *
from MSSpectrum  cimport *
from ChromatogramPeak cimport *
from Peak1D cimport *
from String cimport *
from ProgressLogger cimport *
from streampos cimport *

cdef extern from "<OpenMS/FORMAT/CachedMzML.h>" namespace "OpenMS":

    # Do not use this class directly, rather use SpectrumAccessOpenMSCached

    cdef cppclass CachedmzML(ProgressLogger):
        # wrap-inherits:
        #   ProgressLogger

        CachedmzML() nogil except +
        CachedmzML(CachedmzML) nogil except +

        void writeMemdump(MSExperiment[Peak1D,ChromatogramPeak] exp, String out) nogil except +
        void writeMetadata(MSExperiment[Peak1D,ChromatogramPeak] exp, String out_meta) nogil except +

        void readMemdump(MSExperiment[Peak1D,ChromatogramPeak] exp, String filename) nogil except +

        # void readSingleSpectrum(MSSpectrum[ Peak1D ] & spectrum, String & filename, Size & idx) nogil except +
        libcpp_vector[ streampos ]  getSpectraIndex() nogil except +
        libcpp_vector[ streampos ]  getChromatogramIndex() nogil except +
        void createMemdumpIndex(String filename) nogil except +
        # NAMESPACE # void readSingleSpectrum(MSSpectrum[ Peak1D ] & spectrum, std::ifstream & ifs, Size & idx)
        # NAMESPACE # void readSpectrumFast(OpenSwath::BinaryDataArrayPtr data1, OpenSwath::BinaryDataArrayPtr data2, std::ifstream & ifs, int ms_level, double rt)
        # NAMESPACE # void readChromatogramFast(OpenSwath::BinaryDataArrayPtr data1, OpenSwath::BinaryDataArrayPtr data2, std::ifstream & ifs)
