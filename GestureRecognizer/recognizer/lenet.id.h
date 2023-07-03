#ifndef NCNN_INCLUDE_GUARD_lenet_id_h
#define NCNN_INCLUDE_GUARD_lenet_id_h
namespace lenet_param_id {
    const int LAYER_data = 0;
    const int BLOB_data = 0;
    const int LAYER_conv1 = 1;
    const int BLOB_conv1 = 1;
    const int LAYER_pool1 = 2;
    const int BLOB_pool1 = 2;
    const int LAYER_conv2 = 3;
    const int BLOB_conv2 = 3;
    const int LAYER_pool2 = 4;
    const int BLOB_pool2 = 4;
    const int LAYER_ip1 = 5;
    const int BLOB_ip1 = 5;
    const int LAYER_relu1 = 6;
    const int BLOB_ip1_relu1 = 6;
    const int LAYER_ip2 = 7;
    const int BLOB_ip2 = 7;
    const int LAYER_prob = 8;
    const int BLOB_prob = 8;
} // namespace lenet_param_id
#endif // NCNN_INCLUDE_GUARD_lenet_id_h
