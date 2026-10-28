# CMF 编译环境制作

docker build -f ".gitcode/dockerfiles/Dockerfile.openeuler_22.03_LTS_SP4" -t "openeuler22.03_lts_sp4:arm_kvecturbo_v1.0" . || true
docker tag "openeuler22.03_lts_sp4:arm_kvecturbo_v1.0" "swr.cn-north-4.myhuaweicloud.com/cloud_boostkit/openeuler22.03_lts_sp4:arm_kvecturbo_v1.0" || true
